# Android port of [pdf2htmlEX](https://github.com/pdf2htmlEX/pdf2htmlEX)

[![Maven Central](https://img.shields.io/maven-central/v/com.viliussutkus89/pdf2htmlex-android.svg?label=Maven%20Central)](https://search.maven.org/search?q=g:com.viliussutkus89%20AND%20a:pdf2htmlex-android)

### Goals:
* Providing easy to use interface for downstream users.  
Library is consumed through gradle and used through a Java class, which provides a method to perform conversion.
* Keeping device requirements low.  
Current versions of NDK support building for Android-16 (Jelly Bean) and newer.  
Supported ABIs: armeabi-v7a, arm64-v8a, x86, x86_64.
* Keeping installed footprint low.  
Sample application consumes under 30MB.

### C++ runtime dependency:
[Using mismatched prebuilt libraries](https://android.googlesource.com/platform/ndk/+/master/docs/user/common_problems.md#using-mismatched-prebuilt-libraries) is less problematic if all the libraries used in the application are:
* Built with the same toolchain - ndk-22.0.7026061
* Linked against shared C++ STL - `android.defaultConfig.externalNativeBuild.cmake.arguments "-DANDROID_STL=c++_shared"` in app's (and all JNI dependencies) build.gradle.

### How to install:
[android-sample-app/app/build.gradle](android-sample-app/app/build.gradle) contains code to load the library as a dependency in Gradle.
```gradle
dependencies {
    implementation 'com.viliussutkus89:pdf2htmlex-android:0.18.12'
}
```

pdf2htmlEX-Android is distributed using [Maven Central](https://search.maven.org/artifact/com.viliussutkus89/pdf2htmlex-android) repository.  
It needs be added to [top level build.gradle](android-sample-app/build.gradle)
```gradle
allprojects {
  repositories {
      // ...
      mavenCentral()
  }
}
```

### Usage:
Library is interfaced through Java.
```Java
import com.viliussutkus89.android.pdf2htmlex.pdf2htmlEX;
...
java.io.File inputPdf = new java.io.File(getFilesDir(), "my.pdf");
java.io.File outputHTML = new pdf2htmlEX(getApplicationContext()).setInputPDF(inputPdf).convert();
```

Encrypted PDF documents need a password to be decrypted.

Either owner (admin):
```Java
java.io.File outputHTML = new pdf2htmlEX(getApplicationContext()).setInputPDF(inputPdf).setOwnerPassword("owner-password").convert();
```
or user password can be used:
```Java

java.io.File outputHTML = new pdf2htmlEX(getApplicationContext()).setInputPDF(inputPdf).setUserPassword("user-password").convert();
```

Library needs Android Context to obtain path to cache directory and asset files, which are supplied in .aar.

### Problem scope:
pdf2htmlEX depends on 4 libraries:
* Cairo
* FontForge
* FreeType
* Poppler

These libraries also have dependencies of their own. FontForge requires FreeType, libjpeg, zlib, et cetera.
Full list of packages and patches to build them is included in [packages](/dependency-builder/src/main/cpp/packages/) folder.

### CMake Superbuild pattern
[DependencyBuilder](/dependency-builder/src/main/cpp/CMakeLists.txt) is a meta project which builds it's
[ExternalProjects](https://cmake.org/cmake/help/latest/module/ExternalProject.html) (Cairo, FontForge, et cetera).
Current implementation supports building projects which are based on [Autotools](/dependency-builder/src/main/cpp/EPAutotools.cmake), [CMake](/dependency-builder/src/main/cpp/EPCMake.cmake) and [Meson](/dependency-builder/src/main/cpp/EPMeson.cmake).

[pdf2htmlEX-Android](pdf2htmlEX/src/main/cpp/CMakeLists.txt) consumes previously built libraries and provides a Java wrapper to call pdf2htmlEX.

### [Sample application](/android-sample-app)
Example demonstrates how to convert PDF files to HTML and either open the result in browser or save to storage.
Storage Access Framework (SAF) is used for file management, it requires API level 19 (KitKat).
Debug build of sample application is available in [Releases Page](https://github.com/ViliusSutkus89/pdf2htmlEX-Android/releases)

### Tools to build from source:
* Meson Build system (version 0.54.2 or newer)
* pkg-config
* CMake-3.10.2
* ndk-22.0.7026061
* gettext
* gperf

