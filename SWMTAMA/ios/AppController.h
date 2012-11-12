//
//  SWMTAMAAppController.h
//  SWMTAMA
//
//  Created by Jung Hanter on 12. 11. 8..
//  Copyright __MyCompanyName__ 2012년. All rights reserved.
//

@class RootViewController;

@interface AppController : NSObject <UIAccelerometerDelegate, UIAlertViewDelegate, UITextFieldDelegate,UIApplicationDelegate> {
    UIWindow *window;
    RootViewController    *viewController;
}

@end

