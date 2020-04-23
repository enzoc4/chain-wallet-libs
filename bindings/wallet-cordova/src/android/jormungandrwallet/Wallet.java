package com.iohk.jormungandrwallet;

public class Wallet {
    static {
        System.loadLibrary("wallet_jni");
    }

    public native static long recover(String mnemonics);

    public native static void delete(long wallet);

    public native static int totalValue(long wallet);

    public native static long initialFunds(long wallet, byte[] block0);
}