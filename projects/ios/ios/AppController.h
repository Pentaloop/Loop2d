//
//  AppController.h
//  test
//
//  Created by Haseeb Yousaf on 1/3/12.
//  Copyright Penta::Loop inc. 2012. All rights reserved.
//

@class RootViewController;

@interface AppController : NSObject <UIAccelerometerDelegate, UIAlertViewDelegate, UITextFieldDelegate,UIApplicationDelegate> {
    UIWindow *window;
    RootViewController	*viewController;
}

@end

