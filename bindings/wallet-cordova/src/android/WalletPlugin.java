package com.iohk.jormungandrwallet;

import java.util.concurrent.Callable;
import java.util.concurrent.Future;
import java.text.Normalizer;
import java.text.Normalizer.Form;

import com.iohk.jormungandrwallet.Settings;
import com.iohk.jormungandrwallet.Wallet;
import com.iohk.jormungandrwallet.Conversion;

import org.apache.cordova.CallbackContext;
import org.apache.cordova.CordovaInterface;
import org.apache.cordova.CordovaPlugin;
import org.apache.cordova.CordovaWebView;
import org.apache.cordova.CordovaArgs;
import org.json.JSONArray;
import org.json.JSONException;

import android.util.Base64;
import android.util.Log;

public class WalletPlugin extends CordovaPlugin {
    public static final String TAG = "WALLET";

    /**
     * Constructor.
     */
    public WalletPlugin() {
    }

    /**
     * Sets the context of the Command. This can then be used to do things like get
     * file paths associated with the Activity.
     *
     * @param cordova The context of the main Activity.
     * @param webView The CordovaWebView Cordova is running in.
     */
    public void initialize(final CordovaInterface cordova, final CordovaWebView webView) {
        super.initialize(cordova, webView);
        Log.d(TAG, "Initializing wallet plugin");
    }

    /**
     * Executes the request and returns PluginResult.
     *
     * @param action          The action to execute.
     * @param args            JSONArry of arguments for the plugin.
     * @param callbackContext The callback id used when calling back into
     *                        JavaScript.
     * @return True if the action was valid, false if not.
     */

    public boolean execute(final String action, final CordovaArgs args, final CallbackContext callbackContext)
            throws JSONException {
        Log.d(TAG, "action: " + action);
        switch (action) {
            case "WALLET_RESTORE":
                walletRestore(args, callbackContext);
                break;
            case "WALLET_RETRIEVE_FUNDS":
                walletRetrieveFunds(args, callbackContext);
                break;
            case "WALLET_TOTAL_FUNDS":
                walletTotalFunds(args, callbackContext);
                break;
            case "WALLET_ID":
                walletId(args, callbackContext);
                break;
            case "WALLET_CONVERT":
                walletConvert(args, callbackContext);
                break;
            case "CONVERSION_TRANSACTIONS_SIZE":
                conversionTransactionsSize(args, callbackContext);
                break;
            case "CONVERSION_TRANSACTIONS_GET":
                conversionTransactionsGet(args, callbackContext);
                break;
            case "WALLET_DELETE":
                walletDelete(args, callbackContext);
                break;
            case "SETTINGS_DELETE":
                settingsDelete(args, callbackContext);
                break;
            case "CONVERSION_DELETE":
                conversionDelete(args, callbackContext);
                break;
            default:
                return false;
        }

        return true;
    }

    private void walletRestore(final CordovaArgs args, final CallbackContext callbackContext) throws JSONException {
        final String mnemonics = args.getString(0);

        cordova.getThreadPool().execute(new Runnable() {
            public void run() {
                try {
                    final String normalized = Normalizer.normalize(mnemonics, Form.NFKD);
                    final long walletPtr = Wallet.recover(normalized);
                    callbackContext.success(Long.toString(walletPtr));
                } catch (final Exception e) {
                    callbackContext.error(e.getMessage());
                }
            }
        });
    }

    private void walletRetrieveFunds(final CordovaArgs args, final CallbackContext callbackContext)
            throws JSONException {
        final Long walletPtr = args.getLong(0);
        final byte[] block0 = args.getArrayBuffer(1);

        cordova.getThreadPool().execute(new Runnable() {
            public void run() {
                try {
                    final long settingsPtr = Wallet.initialFunds(walletPtr, block0);
                    callbackContext.success(Long.toString(settingsPtr));
                } catch (final Exception e) {
                    callbackContext.error(e.getMessage());
                }
            }
        });
    }

    private void walletTotalFunds(final CordovaArgs args, final CallbackContext callbackContext) throws JSONException {
        final Long walletPtr = args.getLong(0);

        try {
            final int value = Wallet.totalValue(walletPtr);
            callbackContext.success(Integer.toString(value));
        } catch (final Exception e) {
            callbackContext.error(e.getMessage());
        }
    }

    private void walletConvert(final CordovaArgs args, final CallbackContext callbackContext) throws JSONException {
        final Long walletPtr = args.getLong(0);
        final Long settingsPtr = args.getLong(1);

        cordova.getThreadPool().execute(new Runnable() {
            public void run() {
                try {
                    final long conversionPtr = Wallet.convert(walletPtr, settingsPtr);
                    callbackContext.success(Long.toString(conversionPtr));
                } catch (final Exception e) {
                    callbackContext.error(e.getMessage());
                }
            }
        });
    }

    private void conversionTransactionsSize(final CordovaArgs args, final CallbackContext callbackContext)
            throws JSONException {
        final Long conversionsPtr = args.getLong(0);

        try {
            final int size = Conversion.transactionsSize(conversionsPtr);
            callbackContext.success(Integer.toString(size));
        } catch (final Exception e) {
            callbackContext.error(e.getMessage());
        }
    }

    private void conversionTransactionsGet(final CordovaArgs args, final CallbackContext callbackContext)
            throws JSONException {
        final Long conversionsPtr = args.getLong(0);
        final int index = args.getInt(1);

        try {
            final byte[] transaction = Conversion.transactionsGet(conversionsPtr, index);
            callbackContext.success(transaction);
        } catch (final Exception e) {
            callbackContext.error(e.getMessage());
        }
    }

    private void walletId(final CordovaArgs args, CallbackContext callbackContext) throws JSONException {
        final Long walletPtr = args.getLong(0);

        try {
            byte[] id = Wallet.id(walletPtr);
            callbackContext.success(id);
        } catch (Exception e) {
            callbackContext.error(e.getMessage());
        }
    }

    private void walletDelete(final CordovaArgs args, final CallbackContext callbackContext) throws JSONException {
        final Long walletPtr = args.getLong(0);

        Wallet.delete(walletPtr);
        callbackContext.success();
    }

    private void settingsDelete(final CordovaArgs args, final CallbackContext callbackContext) throws JSONException {
        final Long settingsPtr = args.getLong(0);

        Settings.delete(settingsPtr);
        callbackContext.success();
    }

    private void conversionDelete(final CordovaArgs args, final CallbackContext callbackContext) throws JSONException {
        final Long conversionPtr = args.getLong(0);

        Conversion.delete(conversionPtr);
        callbackContext.success();
    }
}
