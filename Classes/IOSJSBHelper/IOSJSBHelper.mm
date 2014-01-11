//
//  IOSJSBHelper.m
//  ChallengeJS
//
//  Created by Simon on 14/1/9.
//
//

#import "IOSJSBHelper.h"
#import "NDKHelper.h"
#import "JSBHelper.h"

@implementation IOSJSBHelper

+(void)SendMessageToJS:(NSString *)methodName WithParameters:(NSDictionary *)prms
{
//    NSLog(@"into SendMessageToJS");
    json_t* jsonMethod = json_string([methodName UTF8String]);
    json_t *jsonPrms = NULL;
//    NSLog(@"methodName: %s",[methodName UTF8String]);
    
    if (prms != nil)
    {
        NSError *error = nil;
        NSData *jsonData = [NSJSONSerialization
                            dataWithJSONObject:prms
                            options:NSJSONWritingPrettyPrinted
                            error:&error];
        
        if (error != nil)
            return;
        
        NSString *jsonPrmsString = [[NSString alloc] initWithData:jsonData
                                                         encoding:NSUTF8StringEncoding];
        
        //這裡已經變成json了
//        NSLog(@"jsonPrmsString: %@",jsonPrmsString);
        
        json_error_t jerror;
        jsonPrms = json_loads([jsonPrmsString UTF8String], 0, &jerror);
        
        if (!jsonPrms)
        {
            fprintf(stderr, "error: on line %d: %s\n", jerror.line, jerror.text);
            return;
        }
        
        JSBHelper::HandleMessage(jsonMethod, jsonPrms);

        [jsonPrmsString release];
        jsonPrmsString = nil;


    }else{
        JSBHelper::HandleMessage(jsonMethod, jsonPrms);

    }
    
    json_decref(jsonMethod);
    
    if (jsonPrms)
        json_decref(jsonPrms);
}
@end
