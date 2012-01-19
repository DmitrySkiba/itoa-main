This project implements UIKit, QuartzCore and CoreGraphics libraries for Android.

Implementation is based on Android UI classes, which are accessed via JNI. For example CGContext is based on android.graphics.Canvas class, UIButton is a android.widget.Button and so on.

NOTE: UIKit source is not available for the moment - it is being rewritten from ObjC++ frankenstein to straight and clean ObjC.