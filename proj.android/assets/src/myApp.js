/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2011      Zynga Inc.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

var MyLayer = cc.Layer.extend({
    isMouseDown:false,
    helloImg:null,
    helloLabel:null,
    circle:null,
    sprite:null,

    ctor:function() {
        this._super();
        cc.associateWithNative( this, cc.Layer );
    },

    init:function () {

        this._super();

        if( sys.os == "android" || sys.os == "Android") {
            this.setKeypadEnabled(true);
        }

        var size = cc.Director.getInstance().getWinSize();

        var btn_callToCpp = cc.MenuItemImage.create(
            "res/calltocpp.png",
            "res/calltocpp_o.png",
            function () {

                var map = {};
                map["message"]="I am caller from Javascript";


                // [Manner first.]
                //First manner to declare call Cpp function with callback.
                JSBHelper.AddSelector("helloJS",this.helloJS);
                SendMessageToCpp("helloCpp", map);

                //[Manner second.]
//                SendMessageToCppWithCallbackName("helloCpp",null,"helloJS",this.helloJS);


            },this);
        btn_callToCpp.setAnchorPoint(cc.p(0.5, 0.5));
        btn_callToCpp.setPosition(cc.p(size.width - 100, 60));
        var menu = cc.Menu.create(btn_callToCpp);
        menu.setPosition(cc.p(0, 0));
        this.addChild(menu, 1);

        var btn_callToNative = cc.MenuItemImage.create(
            "res/calltonative.png",
            "res/calltonative_o.png",
            function () {

                var map = {};
                map["message"]="I am caller from Javascript";


                // [Manner first.]
                //First manner to declare call Cpp function with callback.
//                JSBHelper.AddSelector("helloJS",this.helloJS);
//                SendMessageToNativeWithCallbackName("helloNative", map);

                //[Manner second.]
//                SendMessageToNativeWithCallbackName("helloNative",map,"helloJS",this.helloJS);
                SendMessageToNativeWithCallbackName("helloNative",null,null,null);

//                SendMessageToNative("helloNative",map);
//                SendMessageToNative("helloNative",null);

            },this);
        btn_callToNative.setAnchorPoint(cc.p(0.5, 0.5));
        btn_callToNative.setPosition(cc.p(size.width - 100, 20));
        var menu2 = cc.Menu.create(btn_callToNative);
        menu2.setPosition(cc.p(0, 0));
        this.addChild(menu2, 1);


        this.sprite = cc.Sprite.create("res/HelloWorld.png");
        this.sprite.setAnchorPoint(cc.p(0.5, 0.5));
        this.sprite.setPosition(cc.p(size.width / 2, size.height / 2));

        this.addChild(this.sprite, 0);

        return true;
    },
    backClicked : function(){
        cc.log("into backClicked");
        cc.Director.getInstance().end();
    },
    helloJS : function helloJS (returnValue) {
        cc.log("This is method: helloJS in Javascript, get parameter: "+returnValue);
        var ob = JSON.parse(returnValue);
        for(key in ob){
            cc.log("key: "+key+", value: "+ob[key]);
        }
    }
});

var MyScene = cc.Scene.extend({
    ctor:function() {
        this._super();
        cc.associateWithNative( this, cc.Scene );
    },

    onEnter:function () {
        this._super();
        var layer = new MyLayer();
        this.addChild(layer);
        layer.init();



    }
});
