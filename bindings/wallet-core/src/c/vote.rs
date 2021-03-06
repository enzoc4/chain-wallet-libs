use super::ProposalPtr;
use crate::{
    vote::{EncryptingVoteKey, PayloadTypeConfig},
    Error, Proposal, Result as AbiResult,
};
use chain_impl_mockchain::{certificate::VotePlanId, vote::Options as VoteOptions};
use std::convert::TryFrom;
use thiserror::Error;
pub use wallet::Settings;

const ENCRYPTION_VOTE_KEY_SIZE: usize = 65;

// using generics in this module is questionable, but it's used just for code
// re-use, the idea is to have two functions, and then it's exposed that way in
// wallet-c/wallet-jni (with manual name mangling).
// for the C interface, a tagged union could be used as input too, but I think
// using the same approach for all the interfaces it's better.
// something else that could work is a new opaque type.
pub struct ProposalPublic;
#[repr(transparent)]
pub struct ProposalPrivate(pub *const u8);

#[derive(Error, Debug)]
#[error("invalid binary format")]
pub struct InvalidEncryptionKey;

pub trait ToPayload {
    fn to_payload(self) -> Result<PayloadTypeConfig, Error>;
}

impl ToPayload for ProposalPublic {
    fn to_payload(self) -> Result<PayloadTypeConfig, Error> {
        Ok(PayloadTypeConfig::Public)
    }
}

impl ToPayload for ProposalPrivate {
    fn to_payload(self) -> Result<PayloadTypeConfig, Error> {
        if self.0.is_null() {
            Err(Error::invalid_input("encrypting_vote_key").with(crate::c::NulPtr))
        } else {
            unsafe {
                let encryption_vote_key =
                    std::slice::from_raw_parts(self.0, ENCRYPTION_VOTE_KEY_SIZE);

                EncryptingVoteKey::from_bytes(encryption_vote_key)
                    .ok_or_else(|| {
                        Error::invalid_input("encrypting_vote_key").with(InvalidEncryptionKey)
                    })
                    .map(PayloadTypeConfig::Private)
            }
        }
    }
}

/// build the proposal object
///
/// # Errors
///
/// This function may fail if:
///
/// * a null pointer was provided as an argument.
/// * `num_choices` is out of the allowed range.
///
/// # Safety
///
/// This function dereference raw pointers. Even though the function checks if
/// the pointers are null. Mind not to put random values in or you may see
/// unexpected behaviors.
pub unsafe fn proposal_new<P: ToPayload>(
    vote_plan_id: *const u8,
    index: u8,
    num_choices: u8,
    payload_type: P,
    proposal_out: *mut ProposalPtr,
) -> AbiResult {
    let options = match VoteOptions::new_length(num_choices) {
        Ok(options) => options,
        Err(err) => return Error::invalid_input("num_choices").with(err).into(),
    };

    let vote_plan_id = non_null_array!(vote_plan_id, crate::vote::VOTE_PLAN_ID_LENGTH);
    let vote_plan_id = match VotePlanId::try_from(vote_plan_id) {
        Ok(id) => id,
        Err(err) => return Error::invalid_input("vote_plan_id").with(err).into(),
    };

    let payload_type = match payload_type.to_payload() {
        Ok(payload_type) => payload_type,
        Err(err) => return err.into(),
    };

    let proposal = Proposal::new(vote_plan_id, index, options, payload_type);
    *non_null_mut!(proposal_out) = Box::into_raw(Box::new(proposal));

    AbiResult::success()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn cast_private_vote() {
        use chain_vote::gargamel;
        use rand::SeedableRng;
        let vote_plan_id = [0u8; crate::vote::VOTE_PLAN_ID_LENGTH];
        let mut rng = rand_chacha::ChaCha20Rng::from_seed([1u8; 32]);
        let sk = gargamel::SecretKey::generate(&mut rng);
        let pk = gargamel::Keypair::from_secretkey(sk).public_key;

        let encrypting_vote_key = pk.to_bytes();
        let mut proposal: ProposalPtr = std::ptr::null_mut();
        unsafe {
            let result = proposal_new(
                vote_plan_id.as_ptr(),
                0,
                2,
                ProposalPrivate(encrypting_vote_key.as_ptr()),
                (&mut proposal) as *mut ProposalPtr,
            );
            assert!(result.is_ok());
        }
    }
}
