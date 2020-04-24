# README

## Testing

The tests use [cordova-plugin-test-framework](https://github.com/apache/cordova-plugin-test-framework).

** TLDR ** (for android)

```sh
cd $TEST_APP_DIRECTORY 
cordova create hello com.example.hello HelloWorld
cd hello
cordova platform add android 
cordova plugin add cordova-plugin-test-framework
cordova plugin add path-to-wallet-cordova
cordova plugin add path-to-wallet-cordova/tests
sed 's/<content src="index.html" \/>/<content src="cdvtests\/index.html" \/>/' config.xml -i
cordova build
cordova run android
```