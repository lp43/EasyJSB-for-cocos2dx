
#import "RootViewController.h"
#import "IOSNDKHelper.h"
#import "IOSJSBHelper.h"

@implementation RootViewController

/*
 // The designated initializer.  Override if you create the controller programmatically and want to perform customization that is not appropriate for viewDidLoad.
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    if ((self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil])) {
        // Custom initialization
    }
    return self;
}
*/

/*
// Implement loadView to create a view hierarchy programmatically, without using a nib.
- (void)loadView {
}
*/

/*
// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];
}
 
*/
// Override to allow orientations other than the default portrait orientation.
// This method is deprecated on ios6
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    return UIInterfaceOrientationIsLandscape( interfaceOrientation );
}

// For ios6, use supportedInterfaceOrientations & shouldAutorotate instead
- (NSUInteger) supportedInterfaceOrientations{
#ifdef __IPHONE_6_0
    return UIInterfaceOrientationMaskAllButUpsideDown;
#endif
}

- (BOOL) shouldAutorotate {
    return YES;
}

//fix not hide status on ios7
- (BOOL)prefersStatusBarHidden
{
    return YES;
}

- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

- (void)viewDidUnload {
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    if ((self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil])) {
        
        // 告訴NDKHelper說 RootViewController會回應來自C++的message
        [IOSNDKHelper SetNDKReciever:self];
        
    }
    return self;
}

- (void) helloNative:(NSObject *)prms{
    NSLog(@"this is method: helloNative in ios, prms is: %@",prms);
    
    NSDictionary *dictionary = [NSDictionary dictionaryWithObjectsAndKeys:[NSString stringWithFormat:@"hello, i am message from native ios"],@"message", nil];
    //    [IOSNDKHelper SendMessage:@"helloJS" WithParameters:dictionary];
    [IOSJSBHelper SendMessageToJS:@"helloJS" WithParameters:dictionary];
}
- (void)dealloc {
    [super dealloc];
}


@end
