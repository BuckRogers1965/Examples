if (typeof(CDS) == 'undefined')
{
    var CDS = {
    SyndicatorID:                 null,
    ProductID:                    null,
    GeoLang:                      null,
    ContentItemButtonHTML:        null,
    ContentItemInlineTitleHTML:   null, // new
    Modules:{
      MoreInfo:0,
      Screenshots:{
         Thumbnails:100,
         FullSize:101
      }
    },
    ProductModuleButtonHTML:      null,
    ProductModuleInlineTitleHTML: null,
    ChannelID:                    null,
    ChannelFormFactor:            null,
    ChannelDefaultHTML:           null,
    ContentItemID:                null,
    
    GetProductModuleButton:function (Module) {
        if(CDS.SyndicatorID == null || CDS.SyndicatorID == "")
        {
            return;
        }
         
        if(Module != CDS.Modules.MoreInfo)
        {
            return;
        }
         
        CDS.Private.gProductInfoModule = Module;
        CDS.Private.gProductInfoFormFactor = 1; 
        var myprivate = new CDS.Private(CDS.SyndicatorID, CDS.ProductID, CDS.GeoLang, CDS.ContentItemButtonHTML, CDS.ProductModuleButtonHTML, CDS.ProductModuleInlineTitleHTML, CDS.ChannelID, CDS.ContentItemID, CDS.ChannelFormFactor, CDS.ChannelDefaultHTML);
        myprivate.GetProductModuleButton();
    },
         
    GetProductModuleInline:function (Module) {
        if(CDS.SyndicatorID == null || CDS.SyndicatorID == "")
        {
            return;
        }
         
        if(Module != CDS.Modules.MoreInfo)
        {
            return;
        }
        
        CDS.Private.gProductInfoModule = Module;
        CDS.Private.gProductInfoFormFactor = 0; 
         var myprivate = new CDS.Private(CDS.SyndicatorID, CDS.ProductID, CDS.GeoLang, CDS.ContentItemButtonHTML, CDS.ProductModuleButtonHTML, CDS.ProductModuleInlineTitleHTML, CDS.ChannelID, CDS.ContentItemID, CDS.ChannelFormFactor, CDS.ChannelDefaultHTML);
         myprivate.GetProductModuleInline();
    },
    
    GetChannelFormFactorInline:function () {
        if(CDS.SyndicatorID == null || CDS.SyndicatorID == "")
        {
            return;
        }
         
        var myprivate = new CDS.Private(CDS.SyndicatorID, CDS.ProductID, CDS.GeoLang, CDS.ContentItemButtonHTML, CDS.ProductModuleButtonHTML, CDS.ProductModuleInlineTitleHTML, CDS.ChannelID, CDS.ContentItemID, CDS.ChannelFormFactor, CDS.ChannelDefaultHTML);
        myprivate.GetChannelFormFactorInline();
    },
    
    GetContentItemInline:function () {
        if(CDS.SyndicatorID == null || CDS.SyndicatorID == "")
        {
            return;
        }
        CDS.Private.gProductInfoModule = CDS.Modules.MoreInfo;
        CDS.Private.gProductInfoFormFactor = 2; 
        var myprivate = new CDS.Private(CDS.SyndicatorID, CDS.ProductID, CDS.GeoLang, CDS.ContentItemButtonHTML, CDS.ProductModuleButtonHTML, CDS.ProductModuleInlineTitleHTML, CDS.ChannelID, CDS.ContentItemID, CDS.ChannelFormFactor, CDS.ChannelDefaultHTML);
        myprivate.GetContentItemInline();
    },
    
    GetContentItemButton:function () {
        if(CDS.SyndicatorID == null || CDS.SyndicatorID == "")
        {
            return;
        }
        CDS.Private.gProductInfoModule = CDS.Modules.MoreInfo;
        CDS.Private.gProductInfoFormFactor = 3; 
        var myprivate = new CDS.Private(CDS.SyndicatorID, CDS.ProductID, CDS.GeoLang, CDS.ContentItemButtonHTML, CDS.ProductModuleButtonHTML, CDS.ProductModuleInlineTitleHTML, CDS.ChannelID, CDS.ContentItemID, CDS.ChannelFormFactor, CDS.ChannelDefaultHTML);
        myprivate.GetContentItemButton();
    }
    };
    
    CDS.Private = function (SyndicatorID, ProductID, GeoLang, ContentItemButtonHTML, ProductModuleButtonHTML, ProductModuleInlineTitleHTML, ChannelID, ContentItemID, ChannelFormFactor, ChannelDefaultHTML)
    {
        CDS.Private.gSyndicatorID = CDS.Private.Utility.Trim(SyndicatorID);
        if(ProductID != null && ProductID != "")
        {
            CDS.Private.gOriginalProductID = ProductID;
            CDS.Private.gProductID = ProductID.replace(/\W/gi, '').toLowerCase();
        }
        
        if(typeof GeoLang == 'undefined' || GeoLang == "")
        {
            CDS.Private.gGeoLang = 'en-us';
        }
        else
        {
            CDS.Private.gGeoLang = CDS.Private.Utility.Trim(GeoLang);
        }
        CDS.Private.gProductModuleButtonHTML = CDS.Private.Utility.Trim(ProductModuleButtonHTML);
        CDS.Private.gProductModuleInlineTitleHTML = CDS.Private.Utility.Trim(ProductModuleInlineTitleHTML);
        CDS.Private.gContentItemButtonHTML = CDS.Private.Utility.Trim(ContentItemButtonHTML);
        CDS.Private.gChannelID = CDS.Private.Utility.Trim(ChannelID);
        CDS.Private.gContentItemID = CDS.Private.Utility.Trim(ContentItemID);
        CDS.Private.gChannelFormFactor = CDS.Private.Utility.Trim(ChannelFormFactor);
        CDS.Private.gChannelDefaultHTML = CDS.Private.Utility.Trim(ChannelDefaultHTML);
    };

    CDS.Private.gContentHostName=CDSBE.BaseURL;
    CDS.Private.gVersionBaseURL = CDSBE.VersionBaseURL;
    CDS.Private.gCoreBaseURL = CDSBE.CoreBaseURL;
    CDS.Private.gSharedBaseURL = CDSBE.SharedBaseURL;
    CDS.Private.gScriptBaseURL = CDSBE.ScriptBaseURL;
    CDS.Private.gCssBaseURL = CDSBE.CssBaseURL;
    CDS.Private.gImagesBaseURL = CDSBE.ImagesBaseURL;
    CDS.Private.gJsonTemplateBaseURL = CDSBE.JsonTemplateBaseURL;
    CDS.Private.gJsonBaseURL = CDSBE.JsonBaseURL;
    CDS.Private.gContentBaseURL = CDSBE.ContentBaseURL;
    CDS.Private.gProductInfoModule = 0;
    CDS.Private.gProductInfoModuleSubType = 0;
    CDS.Private.gProductInfoFormFactor = 0;
    CDS.Private.gProductInfoCustomized = 0;
    CDS.Private.gTimeOut = 200;
    
    CDS.Private.gProductInfoPopupTemplateURL=CDS.Private.gJsonTemplateBaseURL + "ProductInfoPopupTemplate.json?";
    CDS.Private.gProductInfoInlineTemplateURL=CDS.Private.gJsonTemplateBaseURL + "ProductInfoInlineTemplate.json?";
    CDS.Private.gProductInfoDirectoryURL=CDS.Private.gJsonBaseURL;
    CDS.Private.gChannelContentDirectoryURL=CDS.Private.gJsonBaseURL;
    CDS.Private.gCloseButtonImageUri=CDS.Private.gImagesBaseURL + "closebutton.gif";
    //CDS.Private.gCloseButtonImageUri=CDS.Private.gImagesBaseURL + "x.PNG";
    CDS.Private.gCloseButtonMouseOverImageUri=CDS.Private.gImagesBaseURL + "closebutton.gif";
    //CDS.Private.gCloseButtonMouseOverImageUri=CDS.Private.gImagesBaseURL + "close_hover.PNG";
    CDS.Private.gCloseButtonWindowImageUri=CDS.Private.gImagesBaseURL + "closebutton.gif";
    CDS.Private.gCSSPath=CDS.Private.gCssBaseURL;
    CDS.Private.gCSSLinkTagStart=" <link rel='stylesheet' type='text/css' href='";
    CDS.Private.gCSSLinkTagEnd="'/>";
    CDS.Private.gTrackingParameter = "";
    
    CDS.Private.AddEventListener = function (obj, eventType, callbackFunction){ 
       if (obj.addEventListener)
       { 
          obj.addEventListener(eventType, callbackFunction, false); 
          return true; 
       }
       else if (obj.attachEvent)
       { 
          var result = obj.attachEvent("on" + eventType, callbackFunction); 
          return result; 
       }
       else
       { 
          return false; 
       } 
    }
    
    CDS.Private.CreateParamA_S = function(prefix,value){
      if(prefix == null)
         prefix = "?";
         
      return prefix + "A=" + value + "&S=" + CDSBE.IsHttps;
    }
    
    CDS.Private.CreateParamII_CI_V = function(prefix){
      if(prefix == null)
         prefix = "";

      param = prefix;
      param += "&II=" + CDSBE.InstanceID + "&CI=" + CDSBE.ClientID + "&V=" + CDSBE.Version;
      return param;
    }
    
    CDS.Private.CreateParamCB = function(prefix){
      if(prefix == null)
         prefix = "";

      param = prefix;
      param += "&CB=" + CDS.Private.CreateRandom();
      return param;
    }
    
    CDS.Private.CreateParamSI = function(prefix){
      if(prefix == null)
         prefix = "";

      param = prefix;
      param += "&SI=" + CDS.SyndicatorID;
      return param;
    }
    
    CDS.Private.CreateParamSI_GL = function(prefix){
      if(prefix == null)
         prefix = "";

      param = prefix;
      param += "&SI=" + (CDS.SyndicatorID != null ? CDS.SyndicatorID : "");
      param += "&GL=" + (CDS.GeoLang != null ? CDS.GeoLang : "");
      return param;
    }
    
    CDS.Private.CreateParamPI = function(prefix){
      if(prefix == null)
         prefix = "";

      param = prefix;
      param += "&PI=" + CDS.Private.gOriginalProductID;
      return param;
    }
    
    CDS.Private.CreateParamPIM_PIMS_PIF_PIC = function(prefix,pim,pims,pif,pic){
      if(prefix == null)
         prefix = "";

      
      CDS.Private.gProductInfoCustomized = 0;
      switch(CDS.Private.gProductInfoFormFactor)
      {
         case 0:
            if(CDS.ProductModuleInlineTitleHTML != null && CDS.ProductModuleInlineTitleHTML != "")
               CDS.Private.gProductInfoCustomized = 1;
         break;
         case 1:
            if(CDS.ProductModuleButtonHTML != null && CDS.ProductModuleButtonHTML != "")
               CDS.Private.gProductInfoCustomized = 1;
         break;
         case 2:
            if(CDS.ContentItemInlineTitleHTML != null && CDS.ContentItemInlineTitleHTML != "")
               CDS.Private.gProductInfoCustomized = 1;
            CDS.Private.gProductInfoFormFactor-=2;   
         break;
         case 3:
            if(CDS.ContentItemButtonHTML != null && CDS.ContentItemButtonHTML != "")
               CDS.Private.gProductInfoCustomized = 1;
            CDS.Private.gProductInfoFormFactor-=2;   
         break;
      }
      
      param = prefix;
      param += "&PIM=" + (pim != null ? pim : CDS.Private.gProductInfoModule);
      param += "&PIMS=" + (pims != null ? pims : CDS.Private.gProductInfoModuleSubType);
      param += "&PIF=" + (pif != null ? pif : CDS.Private.gProductInfoFormFactor);
      param += "&PIC=" + (pic != null ? pic : CDS.Private.gProductInfoCustomized);
      return param;
    }
    
    CDS.Private.CreateParamCHI = function(prefix, channelId){
      if(prefix == null)
         prefix = "";

      param = prefix;
      param += "&CHI=" + channelId;
      return param;
    }
    
    CDS.Private.CreateParamCHF = function(prefix, channelFormFactor){
      if(prefix == null)
         prefix = "";

      param = prefix;
      param += "&CHF=" + channelFormFactor;
      return param;
    }
    
    CDS.Private.CreateParamIG = function(prefix,url){
      if(prefix == null)
         prefix = "";

      param = prefix;
      param += "&IG=" + (url.match(/^([0-9]|[A-F]|[a-f]){32}[/]/) != null ? url.substring(0,32) : "");
      return param;
    }
    
    CDS.Private.CreateParamD = function(prefix,url){
      if(prefix == null)
         prefix = "";

      param = prefix;
      param += "&d=" + encodeURIComponent(url);
      return param;
    }
    
    CDS.Private.CreateRandom = function(){
      do
      {
         result = Math.random();
      }
      while(result == 0 || result == 1)
      return result.toString().substring(2);
    }
    
    CDS.Private.AddCSS = function () {if (typeof(CDS.Private.CSSAdded) == 'undefined') {
         var param = CDS.Private.CreateParamA_S(null,2);
         param = CDS.Private.CreateParamII_CI_V(param);
         param = CDS.Private.CreateParamSI(param);
         param = CDS.Private.CreateParamCB(param);
         document.write(CDS.Private.gCSSLinkTagStart + CDS.Private.gCSSPath + "CDS.css" + param + CDS.Private.gCSSLinkTagEnd + "<!--[if IE]><link rel='stylesheet' type='text/css' href='" + CDS.Private.gCSSPath +"CDS.IE.css" + param + "'/><![endif]-->");
          CDS.Private.CSSAdded = true;
        }
    };
    
    CDS.Private.AddCSS();
    

    CDS.Private.Utility = function() {};
    CDS.Private.Utility.Trim = function (inString) { return inString;};
    CDS.Private.Utility.IsIE = function () {if (typeof(CDS.Private.Utility.ie) == 'undefined'){
                CDS.Private.Utility.ie = (navigator.userAgent.indexOf('MSIE')>=0 && navigator.userAgent.indexOf('opera')==-1 && document.all)?true:false;}
            return CDS.Private.Utility.ie;
        };
    CDS.Private.Utility.dictLookup =  function(strKeyName) { return (this[strKeyName]);};
    CDS.Private.Utility.dictAdd = function(){ for (c=0; c < CDS.Private.Utility.dictAdd.arguments.length; c+=2) { this[CDS.Private.Utility.dictAdd.arguments[c]] = CDS.Private.Utility.dictAdd.arguments[c+1]; if(typeof(this.length=='undefined')) {this.length=1;} else {this.length++;}} };
    CDS.Private.Utility.dictDelete = function(strKeyName) { for (c=0; c < CDS.Private.Utility.dictDelete.arguments.length; c++) { this[CDS.Private.Utility.dictDelete.arguments[c]] = null; this.length--;} };
    CDS.Private.Utility.windowState = (function(){
        return {
            getScrollX:function(){
                    if(self.pageXOffset)
                        return self.pageXOffset;
                    else if (document.documentElement && document.documentElement.scrollTop)
                        return document.documentElement.scrollLeft;
                    else if (document.body)
                        return document.body.scrollLeft;
            },
            getScrollY:function(){
                    if(self.pageYOffset)
                        return self.pageYOffset;
                    else if (document.documentElement && document.documentElement.scrollTop)
                        return document.documentElement.scrollTop;
                    else if (document.body)
                        return document.body.scrollTop;
            },
            getWidth:function(){
                if (self.innerWidth)
                    return(self.innerWidth);
                else if ( document.documentElement && document.documentElement.clientWidth)
                    return document.documentElement.clientWidth;
                else if (document.body)
                    return document.body.clientWidth;
            },
            getHeight:function(){
                if (self.innerHeight)
                    return(self.innerHeight);
                else if ( document.documentElement && document.documentElement.clientHeight)
                    return document.documentElement.clientHeight;
                else if (document.body)
                    return document.body.clientHeight;
            }
        };
    })();



    CDS.Private.prototype = {
        GetProductModuleButton:function () {
         CDS.Private.ProductInfoPopupButton(CDS.Private.gSyndicatorID, CDS.Private.gProductID, CDS.Private.gProductModuleButtonHTML);
        },
        
        GetProductModuleInline:function () {
         CDS.Private.ProductInfoInline(CDS.Private.gSyndicatorID, CDS.Private.gProductID, CDS.Private.gProductModuleInlineTitleHTML);
        },
        
        GetChannelFormFactorInline:function () {
         CDS.Private.ChannelPromotion(CDS.Private.gSyndicatorID, CDS.Private.gChannelID, CDS.Private.gChannelFormFactor);
        },
        
        GetContentItemInline:function () {
         CDS.Private.ContentItemInline(CDS.Private.gSyndicatorID, CDS.Private.gContentItemID);
        },
        
        GetContentItemButton:function() {
         CDS.Private.ContentInfoPopupButton(CDS.Private.gSyndicatorID, CDS.Private.gContentItemID, CDS.Private.gContentItemButtonHTML);
        },
        
        SyndicatorID: null
    }
    
//DDD-Promotion
    CDS.Private.ChannelPromotion = function (Distributor, Channel, ChannelFormFactor)
    {
        // for each channel promotion that is added to a web page, add an appropriate <img> element
        // to the web page, setting the visibility attribute to false.
        // Keep an dictionary of references to all <img> elements added to the page,
        // organized by Channel & Form Factor.    Once the promotion object loads with all the promotions,
        // go through the dictionary of <img> references & update the src= property of each <img> element
        // with the appropriate src for that channel & ChannelFormFactor.
        
        // if the image subsequently loads correctly, set the visibiltiy property of the <img> element to true
        // to show it.  Otherwise, leave the visibility property set to false.
        
        // note, using document.write() to add new element then subsequently calling getElementByID() to get
        // a reference to the element that was just added.
        // while this looks ugly compared to document.body.appendChild(), there's no way to specify an event
        // handler for onload that takes a paremeter (in this case, we need the event parameter) when using the 
        // appendChild() pattern.  Also, if you do appendChild(), there's not an easy way to ensure that the element appears
        // in the correct location.
        // see http://developer.apple.com/internet/webcontent/eventmodels.html for details.
        
        needDelayedShow = (CDS.Private.ChannelContent.Dictionary==null);
        
        CDS.Private.ChannelContent.GetChannelContent(Channel, ChannelFormFactor);
        this.PromotionItem = new CDS.Private.ChannelPromotion.Item();
        this.PromotionItem.Channel = Channel;
        this.PromotionItem.ChannelFormFactor = ChannelFormFactor;
        this.ElementID = "CDS.Promotion_" + Channel + "_" + ChannelFormFactor + "_" + CDS.Private.ChannelPromotion.imageCounter++;
        this.insertedHTML="<a id='" + this.ElementID + "_anchor' class='CDS_PromotionChannelImage' onclick='CDS.Private.ChannelPromotion.onClick(this,event)'>";
        this.insertedHTML +="<img id='" + this.ElementID + "_image' onload='CDS.Private.ChannelPromotion.onLoad(event)' style='visibility:hidden;display:none' border=0 /></a>"
        document.write(this.insertedHTML);
        this.PromotionItem.ElementReference = document.getElementById(this.ElementID + "_image");
        
        CDS.Private.ChannelPromotion.imgRef.push(this.PromotionItem);
        
        if(needDelayedShow)
            CDS.Private.ChannelContent.CheckStatus();
        else if(CDS.Private.ChannelPromotion.DataLoaded == true)
            CDS.Private.ChannelPromotion.SetLinks();
        
    }

    CDS.Private.ChannelPromotion.prototype = {
        // static image ID counter
        imageCounter: 1
    };
    
    CDS.Private.ChannelPromotion.DataLoaded = false;
    CDS.Private.ChannelPromotion.imageCounter=0;
    CDS.Private.ChannelPromotion.imgRef = new Array();
    
    CDS.Private.ChannelPromotion.onLoad = function(eventref)
    {
        // an animated GIF will cause onload to be fired multiple times in IE, so be prepared to handle that.
        if(CDS.Private.Utility.IsIE())
        {   
            eventref.srcElement.style.visibility="visible";
            eventref.srcElement.style.display="";
        }
        else
        {
            eventref.currentTarget.style.visibility="visible";
            eventref.currentTarget.style.display="";
        }
        return;
    }
    
    CDS.Private.ChannelPromotion.onClick = function(obj,eventref)
    {
        var index;
        index = obj.href.indexOf("&d=");
        var dParam = obj.href.substr(index);
        obj.href = obj.href.substr(0,index);
        
        index = obj.href.indexOf("&CB=");
        if(index > -1)
        {
            obj.href = obj.href.substr(0,index);
        }
        
        obj.href += "&CB="+ CDS.Private.CreateRandom();
        obj.href += dParam;
        return;
    }
    
    CDS.Private.ChannelPromotion.Item = function() {
        this.Channel;
        this.ChannelFormFactor;
        this.ElementReference;
    }
    
    CDS.Private.ChannelContent = function () {}
    CDS.Private.ChannelContent.Dictionary = null;
    CDS.Private.ChannelContent.GetChannelContent = function(ChannelID, ChannelFormFactor)
    {
        if(CDS.Private.ChannelContent.Dictionary==null)
        {
            CDS.Private.ChannelContent.Dictionary = "pending";
            var param = CDS.Private.CreateParamA_S(null,7);
            param = CDS.Private.CreateParamII_CI_V(param);
            param = CDS.Private.CreateParamSI_GL(param);
            param = CDS.Private.CreateParamCHI(param, ChannelID);
            param = CDS.Private.CreateParamCHF(param, ChannelFormFactor);
            param = CDS.Private.CreateParamCB(param);
            this.request = CDS.Private.gChannelContentDirectoryURL + CDS.Private.gGeoLang + "/" + "Promotions.json" + param;
            this.json = new CDS.Private.JSON(this.request);
            this.json.buildScriptTag();
            this.json.addScriptTag();
        }
    }
    
    CDS.Private.ChannelContent.Callback = function (callbackdata)
    {
        CDS.Private.ChannelContent.Dictionary = callbackdata;
    }
    
    CDS.Private.ChannelContent.CheckStatus = function()
    {
      if(CDS.Private.ChannelContent.Dictionary == null
        || CDS.Private.ChannelContent.Dictionary == "pending")
      {
         setTimeout(CDS.Private.ChannelContent.CheckStatus, CDS.Private.gTimeOut);
         return false;
      }
      
      if(CDS.Private.ChannelPromotion.imgRef.length < 1)
      {
         return false;
      }
      
      //setTimeout(CDS.Private.ChannelPromotion.SetLinks, CDS.Private.gTimeOut);
      CDS.Private.ChannelPromotion.SetLinks();
      CDS.Private.ChannelPromotion.DataLoaded = true;
    }
    
    CDS.Private.ChannelPromotion.SetLinks = function()
    {
        if(CDS.Private.ChannelContent.Dictionary != null && CDS.Private.ChannelContent.Dictionary != "pending")
        {
            for(var ThisIndex in CDS.Private.ChannelPromotion.imgRef)
            {
                if(typeof CDS.Private.ChannelPromotion.imgRef[ThisIndex] == 'function')
                  continue;
                  
                var TotalContentItems = 0;
                var ThisItem=CDS.Private.ChannelPromotion.imgRef[ThisIndex];
                if(CDS.Private.ChannelContent.Dictionary[ThisItem.Channel])
                {
                    if(CDS.Private.ChannelContent.Dictionary[ThisItem.Channel].ChannelFormFactors[ThisItem.ChannelFormFactor])
                    {
                        for (var item in CDS.Private.ChannelContent.Dictionary[ThisItem.Channel].ChannelFormFactors[ThisItem.ChannelFormFactor] )
                        {
                            if(typeof CDS.Private.ChannelContent.Dictionary[ThisItem.Channel].ChannelFormFactors[ThisItem.ChannelFormFactor][item] == 'function')
                              continue;
                            TotalContentItems++;
                        }
                        if(TotalContentItems > 0)
                        {
                            var imageSrc="";
                            var anchorHref="";
                            var itemNumber = Math.floor(Math.random()*TotalContentItems);
                            imageSrc = CDS.Private.ChannelContent.Dictionary[ThisItem.Channel].ChannelFormFactors[ThisItem.ChannelFormFactor][itemNumber].SourceURL;
                            anchorHref = CDSBE.HostName + "/ct.aspx" ;
                            //anchorHref = CDS.Private.ChannelContent.Dictionary[ThisItem.Channel].ChannelFormFactors[ThisItem.ChannelFormFactor][itemNumber].ClickthroughURL;
                            var param = CDS.Private.CreateParamA_S(null,9);
                            param = CDS.Private.CreateParamII_CI_V(param);
                            param = CDS.Private.CreateParamSI_GL(param);
                            param = CDS.Private.CreateParamCHI(param, ThisItem.Channel);
                            param = CDS.Private.CreateParamCHF(param, ThisItem.ChannelFormFactor);
                            param = CDS.Private.CreateParamIG(param,imageSrc);
                            param = CDS.Private.CreateParamCB(param);
                            
                            ThisItem.ElementReference.src = imageSrc.substr(0,4) == "http" ? imageSrc : CDS.Private.gContentBaseURL + imageSrc + param;
                            
                            param = CDS.Private.CreateParamA_S(null,10);
                            param = CDS.Private.CreateParamII_CI_V(param);
                            param = CDS.Private.CreateParamSI_GL(param);
                            param = CDS.Private.CreateParamCHI(param, ThisItem.Channel);
                            param = CDS.Private.CreateParamCHF(param, ThisItem.ChannelFormFactor);
                            param = CDS.Private.CreateParamIG(param,imageSrc);
                            anchorHref += param;
                            anchorHref = CDS.Private.CreateParamD(anchorHref,CDS.Private.ChannelContent.Dictionary[ThisItem.Channel].ChannelFormFactors[ThisItem.ChannelFormFactor][itemNumber].ClickthroughURL);
                            
                            if(CDS.Private.Utility.IsIE())
                            {
                                ThisItem.ElementReference.parentElement.href= anchorHref.substr(0,4) == "http" ? anchorHref : CDS.Private.gContentBaseURL + anchorHref;
                                ThisItem.ElementReference.parentElement.target = "_blank";
                            }    
                            else
                            {
                                ThisItem.ElementReference.parentNode.href=anchorHref.substr(0,4) == "http" ? anchorHref : CDS.Private.gContentBaseURL + anchorHref;
                                ThisItem.ElementReference.parentNode.target = "_blank";
                            }    
                            // once we set the values for this element, set the element reference to undefined so we'll know to remove it
                            // from the array of elements references later.
                            delete CDS.Private.ChannelPromotion.imgRef[ThisIndex];
                        }
                    }
                    else
                    {
                      var errImageSrc = CDSBE.ContentBaseURL + "ChiOrChfNotFound.gif";
                      var errParam = CDS.Private.CreateParamA_S(null,8);
                      errParam = CDS.Private.CreateParamII_CI_V(errParam);
                      errParam = CDS.Private.CreateParamSI_GL(errParam);
                      errParam = CDS.Private.CreateParamCHI(errParam, ThisItem.Channel);
                      errParam = CDS.Private.CreateParamCHF(errParam, ThisItem.ChannelFormFactor);
                      errParam = CDS.Private.CreateParamIG(errParam,errImageSrc);
                      errParam = CDS.Private.CreateParamCB(errParam);
                      ThisItem.ElementReference.src = errImageSrc + errParam;
                      
                      delete CDS.Private.ChannelPromotion.imgRef[ThisIndex];
                    }
                } 
            }
        }
        for(var i in CDS.Private.ChannelPromotion.imgRef)
        {
            if(typeof CDS.Private.ChannelPromotion.imgRef[i] == 'function')
              continue;
            while(typeof(CDS.Private.ChannelPromotion.imgRef[i]) == 'undefined' && i < CDS.Private.ChannelPromotion.imgRef.length)
                CDS.Private.ChannelPromotion.imgRef.splice(i, 1)
        }
    }
    
//DDD-ProductInfoInline
    CDS.Private.ProductInfoInline = function (Distributor, ProductID, HTMLSnippet)
    {
        if(HTMLSnippet == null) { HTMLSnippet = ""; }
        this.ElementReference = new CDS.Private.ProductInfo.ElementReference();
        this.ElementReference.ID=ProductID;
        this.ElementReference.ElementID = "CDS.ProductInfoInline." + ProductID + "_" + CDS.Private.ProductInfoInline.ReferenceCounter++;
        this.ElementReference.ElementReference = document.getElementById(this.ElementReference.ElementID);
        if(this.ElementReference.ElementReference == null)
        {
           document.write("<div id='" + this.ElementReference.ElementID + "' class='CDS_ProductInfoInline' style='visibility:hidden;display:none'>" + HTMLSnippet + "</div>");
           this.ElementReference.ElementReference = document.getElementById(this.ElementReference.ElementID);

        }
        var param = CDS.Private.CreateParamA_S(null,6);
        param = CDS.Private.CreateParamII_CI_V(param);
        param = CDS.Private.CreateParamSI_GL(param);
        param = CDS.Private.CreateParamPI(param);
        param = CDS.Private.CreateParamPIM_PIMS_PIF_PIC(param);
        this.ElementReference.ElementParameter = param;
        
        CDS.Private.ProductInfoInline.References.push(this.ElementReference);
        
        needDelayedShow = (CDS.Private.ProductInfoInline.Template == null || CDS.Private.ProductInfo.Dictionary == null);

        CDS.Private.ProductInfoInline.GetTemplate();
        CDS.Private.ProductInfo.GetProductInfo(ProductID);
        // DF: we only need to kick off the timeout once before we load anything (hence the check for null)
        // after the first time the timeout will loop until all items are loaded (we could/should generalize
        // to a more structured watcher in v.next)
        if (needDelayedShow)
            CDS.Private.ProductInfoInline.CheckStatus();
        else if(CDS.Private.ProductInfoInline.DataLoaded == true)
            CDS.Private.ProductInfoInline.ShowContentForLoadedProducts();
    }
    
    CDS.Private.ProductInfoInline.ElementReference = function () {
        this.ID;
        this.ElementID;
        this.ElementReference;
    }
    
    CDS.Private.ProductInfoInline.DataLoaded = false;  
    CDS.Private.ProductInfoInline.ReferenceCounter = 0;
    CDS.Private.ProductInfoInline.References = new Array();
    
    CDS.Private.ProductInfoInline.GetTemplate = function() {
        if(CDS.Private.ProductInfoInline.Template == null)
        {
            CDS.Private.ProductInfoInline.Template = "pending";
            var param = CDS.Private.CreateParamA_S("",4);
            param = CDS.Private.CreateParamII_CI_V(param);
            param = CDS.Private.CreateParamSI_GL(param);
            param = CDS.Private.CreateParamPI(param);
            param = CDS.Private.CreateParamPIM_PIMS_PIF_PIC(param);
            param = CDS.Private.CreateParamCB(param);
            this.request = CDS.Private.gProductInfoInlineTemplateURL + param;
            this.json = new CDS.Private.JSON(this.request);
            this.json.buildScriptTag();
            this.json.addScriptTag();
        }
    }
    
    CDS.Private.ProductInfoInline.TemplateCallback = function(callbackdata)
    {
        CDS.Private.ProductInfoInline.Template=callbackdata;
    }
    
    CDS.Private.ProductInfoInline.CheckStatus = function()
    {
      if(CDS.Private.ProductInfoInline.Template == null
        || CDS.Private.ProductInfoInline.Template == "pending"
        || CDS.Private.ProductInfo.Dictionary == null
        || CDS.Private.ProductInfo.Dictionary == "pending")
      {
         setTimeout(CDS.Private.ProductInfoInline.CheckStatus, CDS.Private.gTimeOut);
         return false;
      }
      
      if(CDS.Private.ProductInfoInline.References.length < 1)
      {
         return false;
      }
      
      //setTimeout(CDS.Private.ProductInfoInline.ShowContentForLoadedProducts, CDS.Private.gTimeOut);
      CDS.Private.ProductInfoInline.ShowContentForLoadedProducts();
      CDS.Private.ProductInfoInline.DataLoaded = true;  
    }
    
    CDS.Private.ProductInfoInline.ShowContentForLoadedProducts = function ()
    {
        if(CDS.Private.ProductInfoInline.Template != null
          && CDS.Private.ProductInfoInline.Template != "pending"
          && CDS.Private.ProductInfo.Dictionary != null
          && CDS.Private.ProductInfo.Dictionary != "pending")
        {
            for(this.InlineReference in CDS.Private.ProductInfoInline.References)
            {
                if(typeof CDS.Private.ProductInfoInline.References[this.InlineReference] == 'function')
                  continue;
                
                if(CDS.Private.ProductInfo.GetProductByProductID(CDS.Private.ProductInfoInline.References[this.InlineReference].ID) != null)
                {
                    CDS.Private.ProductInfoInline.Show(CDS.Private.ProductInfoInline.References[this.InlineReference]);
                    delete CDS.Private.ProductInfoInline.References[this.InlineReference];
                }
            }
            
            for (var i in CDS.Private.ProductInfoInline.References)
            {
                if(typeof CDS.Private.ProductInfoInline.References[i] == 'function')
                  continue;
                while(typeof(CDS.Private.ProductInfoInline.References[i]) == 'undefined' && i < CDS.Private.ProductInfoInline.References.length)
                    CDS.Private.ProductInfoInline.References.splice(i,1);
            }
        }
    }
    
    CDS.Private.ProductInfoInline.Show = function (ElementReference) {
        this.ProductInlineReference = ElementReference.ElementReference;
        if(this.ProductInlineReference != null)
        {
            this.ProductInfo = CDS.Private.ProductInfo.GetProductByProductID(ElementReference.ID);
            if(this.ProductInfo != null
              && CDS.Private.ProductInfoInline.Template != null
              && CDS.Private.ProductInfoInline.Template != "pending"
              && CDS.Private.ProductInfo.Dictionary != null
              && CDS.Private.ProductInfo.Dictionary != "pending")
            {
                CDS.Private.gTrackingParameter = ElementReference.ElementParameter;
                this.HTML = CDS.Private.JSONT(this.ProductInfo, CDS.Private.ProductInfoInline.Template.ProductInfoTemplate);
                if(this.HTML != null && this.HTML !="")
                {
                    this.ProductInlineReference.innerHTML+=this.HTML;
                    this.ProductInlineReference.style.display="";
                    this.ProductInlineReference.style.visibility="visible";
                }
            }
        }
    }
            
//DDD-ProductInfoButton
    CDS.Private.ProductInfoPopupButton = function (Distributor, ProductID, HTMLSnippet)
    {
        this.ElementReference = new CDS.Private.ProductInfo.ElementReference();
        this.ElementReference.ID = ProductID;
        this.ElementReference.ElementID = "CDS.ProductInfoPopupButton." + ProductID + "_" + CDS.Private.ProductInfoPopupButton.ReferenceCounter++;
        this.ElementReference.ElementReference = document.getElementById(this.ElementReference.ElementID);
        this.ElementReference.ElementParameter = null;
        var param = CDS.Private.CreateParamA_S(null,6);
        param = CDS.Private.CreateParamII_CI_V(param);
        param = CDS.Private.CreateParamSI_GL(param);
        param = CDS.Private.CreateParamPI(param);
        param = CDS.Private.CreateParamPIM_PIMS_PIF_PIC(param);
        
        if(this.ElementReference.ElementReference == null)
        {
            if(HTMLSnippet == null) { HTMLSnippet = "More Information..."; }
            document.write("<div id='" + this.ElementReference.ElementID + "' class='CDS_ProductInfoPopupButton' onclick='CDS.Private.ProductInfoPopup.Show(\"" + ProductID + "\", event, \"" + param + "\")' style='display:inline;visibility:hidden;'>" + HTMLSnippet + "</div>");
            this.ElementReference.ElementReference = document.getElementById(this.ElementReference.ElementID);
        }
        CDS.Private.ProductInfoPopupButton.References.push(this.ElementReference);
        
        needDelayedShow = (CDS.Private.ProductInfoPopup.Template == null || CDS.Private.ProductInfo.Dictionary == null);
        
        CDS.Private.ProductInfoPopup.GetTemplate();
        CDS.Private.ProductInfo.GetProductInfo(ProductID);
        if(needDelayedShow)
            CDS.Private.ProductInfoPopup.CheckStatus();
        else if(CDS.Private.ProductInfoPopupButton.DataLoaded == true)
            CDS.Private.ProductInfoPopupButton.ShowButtonsForLoadedProducts();
    }
    
    CDS.Private.ProductInfoPopupButton.DataLoaded = false;
    CDS.Private.ProductInfoPopupButton.ReferenceCounter = 0;
    CDS.Private.ProductInfoPopupButton.References = new Array();
    
    CDS.Private.ProductInfoPopupButton.Show = function (ElementReference) {
        this.PopupButtonReference = ElementReference.ElementReference;
        if(this.PopupButtonReference != null)
            this.PopupButtonReference.style.visibility='visible';
    }
    
//    CDS.Private.ProductInfoPopupButton.Hide = function (ProductID) {
//            this.PopupButtonReference = document.getElementById('CDS.ProductInfoPopupButton.' + ProductID);
//        if(this.PopupButtonReference != null)
//            this.PopupButtonReference.style.visibility='hidden';
//    }

    CDS.Private.ProductInfoPopupButton.ShowButtonsForLoadedProducts = function()
    {
        if(CDS.Private.ProductInfoPopup.Template != null
          && CDS.Private.ProductInfoPopup.Template != "pending"
          && CDS.Private.ProductInfo.Dictionary != null
          && CDS.Private.ProductInfo.Dictionary != "pending")
        {
            for(this.ElementReference in CDS.Private.ProductInfoPopupButton.References)
            {
                if(typeof CDS.Private.ProductInfoPopupButton.References[this.ElementReference] == 'function')
                  continue;
                  
                if(CDS.Private.ProductInfo.GetProductByProductID(CDS.Private.ProductInfoPopupButton.References[this.ElementReference].ID) != null)
                {
                    CDS.Private.ProductInfoPopupButton.Show(CDS.Private.ProductInfoPopupButton.References[this.ElementReference]);
                    delete CDS.Private.ProductInfoPopupButton.References[this.ElementReference];
                }
            }
            
            for (var i in CDS.Private.ProductInfoPopupButton.References)
            {
                if(typeof CDS.Private.ProductInfoPopupButton.References[i] == 'function')
                  continue;
                while(typeof(CDS.Private.ProductInfoPopupButton.References[i] == 'undefined') && i < CDS.Private.ProductInfoPopupButton.References.length)
                    CDS.Private.ProductInfoPopupButton.References.splice(i,1);
            }
        }
        else
        {
            //DDD: Needs some more attention if this happens        
            alert("CDS.Private.ProductInfoPopup.Template = null or pending or CDS.Private.ProductInfo.Dictionary = null or pending");
        }
    }
   
    CDS.Private.ProductInfoPopup = function() {
        
    };
    CDS.Private.ProductInfoPopup.prototype = {
    }
    
    CDS.Private.ProductInfoPopup.Show = function(ProductID, EventReference, Parameter) {
        // if the product info returned is an object, then use the object directly.
        // otherwise, assume the product info is actually a ProductID that is a pointer
        // the the actual product to be used.  This scheme only supports one level of
        // indirection.
        // Dan asked about trying to pass pointers to objects in JSON rather than 
        // passing the ProductID.   It doesn't appear possible to pass object references
        // without implementation of some sort of object request broker.  see
        // http://oss.metaparadigm.com/jsonrpc-1.0/manual.html for more details.
        this.ProductInfo = CDS.Private.ProductInfo.GetProductByProductID(ProductID);
        this.Popup = CDS.Private.ProductInfoPopup.GetPopupElement();
        CDS.Private.ProductInfoPopup.Hide();
        CDS.Private.ProductInfoPopup.ClearContent();
		  CDS.Private.gTrackingParameter = Parameter;
        this.HTML = CDS.Private.JSONT(this.ProductInfo, CDS.Private.ProductInfoPopup.Template.ProductInfoTemplate);
        if(this.HTML != null && this.HTML !='')
        {
            this.Popup.innerHTML=this.HTML;
            CDS.Private.ProductInfoPopup.SetPosition(EventReference);
            CDS.Private.ProductInfoPopup.ShowElements();
        }
        var param = Parameter;
        param = param.replace("?A=6","?A=5")
        param = CDS.Private.CreateParamCB(param);
        tempImage = new Image();
        tempImage.src = CDS.Private.gCloseButtonImageUri + param;    
    }

    CDS.Private.ProductInfoPopup.ShowElements = function () {
        CDS.Private.ProductInfoPopup.GetPopupElement().style.visibility='visible';
        //CDS.Private.ProductInfoPopup.ShowElements.style.visibility='visible';
        CDS.Private.ProductInfoPopup.GetPopupShadowElement().style.visibility='visible';
        if (CDS.Private.Utility.IsIE()) CDS.Private.ProductInfoPopup.GetPopupIFrameElement().style.visibility='visible';
    }
    
    CDS.Private.ProductInfoPopup.Hide = function() {
        if (CDS.Private.Utility.IsIE()) CDS.Private.ProductInfoPopup.GetPopupIFrameElement().style.visibility='hidden';
        CDS.Private.ProductInfoPopup.GetPopupShadowElement().style.visibility='hidden';
        CDS.Private.ProductInfoPopup.GetPopupElement().style.visibility='hidden';
    }
    
    CDS.Private.ProductInfoPopup.ClearContent = function () {if(CDS.Private.ProductInfoPopup.PopupElement!=null){while(CDS.Private.ProductInfoPopup.PopupElement.firstChild){CDS.Private.ProductInfoPopup.PopupElement.removeChild(CDS.Private.ProductInfoPopup.PopupElement.firstChild)}}}
    CDS.Private.ProductInfoPopup.GetTemplate = function () {
      if(CDS.Private.ProductInfoPopup.Template == null)
      {
         CDS.Private.ProductInfoPopup.Template = "pending";
         var param = CDS.Private.CreateParamA_S("",4);
         param = CDS.Private.CreateParamII_CI_V(param);
         param = CDS.Private.CreateParamSI_GL(param);
         param = CDS.Private.CreateParamPI(param);
         param = CDS.Private.CreateParamPIM_PIMS_PIF_PIC(param);
         param = CDS.Private.CreateParamCB(param);
         this.request = CDS.Private.gProductInfoPopupTemplateURL + param;
         this.json = new CDS.Private.JSON(this.request);
         this.json.buildScriptTag();
         this.json.addScriptTag();
      }
    }
    
    CDS.Private.ProductInfoPopup.TemplateCallback = function(callbackdata)
    {
        CDS.Private.ProductInfoPopup.Template=callbackdata;
    }
    
    CDS.Private.ProductInfoPopup.CheckStatus = function()
    {
      if(CDS.Private.ProductInfoPopup.Template == null
        || CDS.Private.ProductInfoPopup.Template == "pending"
        || CDS.Private.ProductInfo.Dictionary == null
        || CDS.Private.ProductInfo.Dictionary == "pending")
      {
         setTimeout(CDS.Private.ProductInfoPopup.CheckStatus, CDS.Private.gTimeOut);
         return false;
      }
      
      if(CDS.Private.ProductInfoPopupButton.References.length < 1)
      {
         return false
      }
      
      //setTimeout(CDS.Private.ProductInfoPopupButton.ShowButtonsForLoadedProducts, CDS.Private.gTimeOut);
      CDS.Private.ProductInfoPopupButton.ShowButtonsForLoadedProducts();
      CDS.Private.ProductInfoPopupButton.DataLoaded = true;
    }

    CDS.Private.ProductInfoPopup.Template = null;
    CDS.Private.ProductInfoPopup.CloseButtonMouseOverImage = new Image();
    CDS.Private.ProductInfoPopup.CloseButtonMouseOverImage.src=CDS.Private.gCloseButtonMouseOverImageUri;
    CDS.Private.ProductInfoPopup.CloseButtonMouseOutImage = new Image();
    CDS.Private.ProductInfoPopup.CloseButtonMouseOutImage.src=CDS.Private.gCloseButtonImageUri;
    CDS.Private.ProductInfoPopup.CloseButtonmouseover = function() {if(document.images) {document['CDS.ProductInfoPopupCloseButton'].src = CDS.Private.ProductInfoPopup.CloseButtonMouseOverImage.src};}
    CDS.Private.ProductInfoPopup.CloseButtonmouseout = function() {if(document.images) {document['CDS.ProductInfoPopupCloseButton'].src = CDS.Private.ProductInfoPopup.CloseButtonMouseOutImage.src};}
    CDS.Private.ProductInfoPopup.CloseButtononclick = function(EventReference) {CDS.Private.ProductInfoPopup.Hide();}
    CDS.Private.ProductInfoPopup.PopupElement = null;
    CDS.Private.ProductInfoPopup.GetPopupElement = function() {
        if(CDS.Private.ProductInfoPopup.PopupElement == null)
        {
            CDS.Private.ProductInfoPopup.PopupElement=document.createElement('div');
            CDS.Private.ProductInfoPopup.PopupElement.id='CDS_ProductInfoPopup';
            CDS.Private.ProductInfoPopup.PopupElement.style.position='absolute';
            CDS.Private.ProductInfoPopup.PopupElement.style.visibility='hidden';
            CDS.Private.ProductInfoPopup.PopupElement.style.display='block';
//            CDS.Private.ProductInfoPopup.PopupElement.style.overflow='auto'
            document.body.appendChild(CDS.Private.ProductInfoPopup.PopupElement);
        }
        return CDS.Private.ProductInfoPopup.PopupElement;
    }
    
    CDS.Private.ProductInfoPopup.PopupShadowElement = null;
    CDS.Private.ProductInfoPopup.GetPopupShadowElement = function() {
        if(CDS.Private.ProductInfoPopup.PopupShadowElement == null)
        {
            CDS.Private.ProductInfoPopup.PopupShadowElement=document.createElement('div');
            CDS.Private.ProductInfoPopup.PopupShadowElement.id='CDS_ProductInfoPopupShadow';
            CDS.Private.ProductInfoPopup.PopupShadowElement.style.position='absolute';
            CDS.Private.ProductInfoPopup.PopupShadowElement.style.visibility='hidden';
            CDS.Private.ProductInfoPopup.PopupShadowElement.style.display='block';
            document.body.appendChild(CDS.Private.ProductInfoPopup.PopupShadowElement);
        }
        return CDS.Private.ProductInfoPopup.PopupShadowElement;
    }
    
    CDS.Private.ProductInfoPopup.ShadowSize = 4;
    CDS.Private.ProductInfoPopup.MaximumWidth = 400;
    CDS.Private.ProductInfoPopup.MinimumWidth = 50;
    CDS.Private.ProductInfoPopup.PopupIFrameElement = null;
    CDS.Private.ProductInfoPopup.GetPopupIFrameElement = function() {
        if(CDS.Private.ProductInfoPopup.PopupIFrameElement == null)
        {
            CDS.Private.ProductInfoPopup.PopupIFrameElement=document.createElement('iframe');
            CDS.Private.ProductInfoPopup.PopupIFrameElement.id='CDS_ProductInfoPopupIFrame';
            CDS.Private.ProductInfoPopup.PopupIFrameElement.frameborder=5;
            CDS.Private.ProductInfoPopup.PopupIFrameElement.src='#';
            CDS.Private.ProductInfoPopup.PopupIFrameElement.style.backgroundColor='White';
            CDS.Private.ProductInfoPopup.PopupIFrameElement.style.zIndex=100;
            CDS.Private.ProductInfoPopup.PopupIFrameElement.style.position='absolute';
            CDS.Private.ProductInfoPopup.PopupIFrameElement.style.visibility='hidden';
            CDS.Private.ProductInfoPopup.PopupIFrameElement.style.display='block';
            document.body.appendChild(CDS.Private.ProductInfoPopup.PopupIFrameElement);
        }
        return CDS.Private.ProductInfoPopup.PopupIFrameElement;
    }
    
    CDS.Private.ProductInfoPopup.SetPosition = function(EventReference) {
        this.pu = CDS.Private.ProductInfoPopup.GetPopupElement();
        this.pus = CDS.Private.ProductInfoPopup.GetPopupShadowElement();
        if(CDS.Private.Utility.IsIE()) this.puIFrame = CDS.Private.ProductInfoPopup.GetPopupIFrameElement();
        
        this.BodyWidth = Math.max(document.body.clientWidth, document.documentElement.clientWidth) - 20;
        this.st = Math.max(document.body.scrollTop,document.documentElement.scrollTop);
        this.leftPos = EventReference.clientX + 10;
        
        //this.pu.style.width=null;
        this.pu.style.left = this.leftPos + "px";
        this.pu.style.top = EventReference.clientY + 10 + this.st + "px";
        
        this.pus.style.left = this.leftPos + CDS.Private.ProductInfoPopup.ShadowSize + "px";
        this.pus.style.top = EventReference.clientY + 10 + this.st + CDS.Private.ProductInfoPopup.ShadowSize + "px";
        
//        if(this.pu.offsetWidth > CDS.Private.ProductInfoPopup.MaximumWidth)
//            this.pu.style.width = CDS.Private.ProductInfoPopup.MaximumWidth + "px";
        
        this.PopupWidth = this.pu.offsetWidth + 20;
        if(this.PopupWidth < CDS.Private.ProductInfoPopup.MinimumWidth)
            this.PopupWidth = CDS.Private.ProductInfoPopup.MinimumWidth;
        
        //this.pu.style.width = this.PopupWidth + "px";
        this.pus.style.width = this.pu.offsetWidth + "px";
        this.pus.style.height = this.pu.offsetHeight + "px";
        
        if((this.leftPos + this.PopupWidth) > this.BodyWidth)
        {
            this.pu.style.left = this.pus.style.left.replace("px","") - ((this.leftPos + this.PopupWidth) - this.BodyWidth) + "px";
            this.pus.style.left = this.pus.style.left.replace("px", "") - ((this.leftPos + this.PopupWidth) - this.BodyWidth) + CDS.Private.ProductInfoPopup.ShadowSize  + "px";
        }
        
        if(CDS.Private.Utility.IsIE())
        {
            this.puIFrame.style.left = this.pu.style.left;
            this.puIFrame.style.top = this.pu.style.top;
            this.puIFrame.style.width = this.pu.offsetWidth + "px";
            this.puIFrame.style.height = this.pu.offsetHeight + "px";
        }
    }
    
//DDD-ContentInline
    CDS.Private.ContentItemInline = function(Distributor, ContentID){
        this.ElementReference = new CDS.Private.ContentInfo.ElementReference();
        this.ElementReference.ID = ContentID;
        this.ElementReference.ElementID = "CDS.ContentItemInline_" + CDS.Private.ContentItemInline.ReferenceCounter++;
        this.ElementReference.ElementReference = document.getElementById(this.ElementReference.ElementID);
        var param = CDS.Private.CreateParamA_S(null,15);
        param = CDS.Private.CreateParamII_CI_V(param);
        param = CDS.Private.CreateParamSI_GL(param);
        param = CDS.Private.CreateParamPIM_PIMS_PIF_PIC(param);
        this.ElementReference.ElementParameter = param;
        
        this.ElementReference.ElementReference = document.getElementById(this.ElementReference.ElementID);
        if(this.ElementReference.ElementReference == null)
        {
            document.write("<div id='" + this.ElementReference.ElementID + "' style='display:inline;visibility:hidden;'></div>");
            this.ElementReference.ElementReference = document.getElementById(this.ElementReference.ElementID);
        }
        CDS.Private.ContentItemInline.References.push(this.ElementReference);
        
        needDelayedShow = (CDS.Private.ContentInfo.Dictionary == null || CDS.Private.ContentItemInline.ReferenceCounter == 1);
        
        CDS.Private.ContentInfo.GetContentInfo(ContentID);
        if(needDelayedShow)
            CDS.Private.ContentItemInline.CheckStatus();
        else if(CDS.Private.ContentItemInline.DataLoaded == true)
            CDS.Private.ContentItemInline.ShowContentForLoadedItems();
    }
    
    CDS.Private.ContentItemInline.DataLoaded = false;
    CDS.Private.ContentItemInline.ReferenceCounter = 0;
    CDS.Private.ContentItemInline.References = new Array();
    
    CDS.Private.ContentItemInline.CheckStatus = function()
    {
      if(CDS.Private.ContentInfo.Dictionary == null
        || CDS.Private.ContentInfo.Dictionary == "pending")
      {
         setTimeout(CDS.Private.ContentItemInline.CheckStatus, CDS.Private.gTimeOut);
         return false;
      }
      
      if(CDS.Private.ContentItemInline.References.length < 1)
      {
         return false;
      }
      
      //setTimeout(CDS.Private.ContentItemInline.ShowContentForLoadedItems, CDS.Private.gTimeOut);
      CDS.Private.ContentItemInline.ShowContentForLoadedItems();
      CDS.Private.ContentItemInline.DataLoaded = true;
    }
    
    CDS.Private.ContentItemInline.ShowContentForLoadedItems = function ()
    {
        if(CDS.Private.ContentInfo.Dictionary != null
          && CDS.Private.ContentInfo.Dictionary != "pending")
        {
            for(this.InlineReference in CDS.Private.ContentItemInline.References)
            {
                if(typeof CDS.Private.ContentItemInline.References[this.InlineReference] == 'function')
                  continue;
                
                if(CDS.Private.ContentInfo.GetContentByContentAlias(CDS.Private.ContentItemInline.References[this.InlineReference].ID) != null)
                {
                    CDS.Private.ContentItemInline.Show(CDS.Private.ContentItemInline.References[this.InlineReference]);
                    delete CDS.Private.ContentItemInline.References[this.InlineReference];
                }
            }
            
            for (var i in CDS.Private.ContentItemInline.References)
            {
                if(typeof CDS.Private.ContentItemInline.References[i] == 'function')
                  continue;
                while(typeof(CDS.Private.ContentItemInline.References[i]) == 'undefined' && i < CDS.Private.ContentItemInline.References.length)
                    CDS.Private.ContentItemInline.References.splice(i,1);
            }
        }
    }
    
    CDS.Private.ContentItemInline.Show = function (ElementReference)
    {
        this.InlineReference = ElementReference.ElementReference;
        if(this.InlineReference != null && ElementReference != null)
        {
            micrositeInfo = CDS.Private.ContentInfo.GetContentByContentAlias(ElementReference.ID);
            if(micrositeInfo != null)
            {
               itemGUID = CDS.Private.ContentInfo.GetContentIDByContentAlias(ElementReference.ID);
               param = ElementReference.ElementParameter;
               param += "&IG=" + itemGUID;
               width = micrositeInfo.width;
               height = micrositeInfo.height;
               url = CDS.Private.gContentBaseURL + micrositeInfo.url + param; 
               url = CDS.Private.CreateParamCB(url);
               frameName = ElementReference.ElementID + "_" + itemGUID;
               
               this.innerHtml ='<iframe';
               this.innerHtml += ' id="' + frameName + '"';
               this.innerHtml += ' name="' + frameName + '"';
               this.innerHtml += ' style="display:inline;" frameborder="0" scrolling="auto" marginwidth="0" marginheight="0"';
               this.innerHtml += " src=" + url + ' width="' + width +'px" height="' + height + 'px"';
               //this.innerHtml += "src=" + url + ' height="' + height + 'px"';
               //this.innerHtml += " onload=CDS.Private.ContentItemInline.ResizeIframe(\"" + frameName + "\")";
               //this.innerHtml += " onload=FrameManager.registerFrame(this)";
               this.innerHtml += '></iframe>'
               this.InlineReference.innerHTML = this.innerHtml;
               this.InlineReference.style.visibility='visible';
            }
        }    
    }
    
    CDS.Private.ContentItemInline.ResizeIframe = function(elemId)
    {
      //alert(document.getElementById(elemId).height=window.frames[elemId].document.body.scrollHeight);
      //alert(document.getElementById(elemId).height=window.frames[elemId].document.body.scrollWidth);
      //alert(window.frames[elemId].document.body.scrollWidth);
    }
    
//DDD-ContentButton
    CDS.Private.ContentInfoPopupButton = function (Distributor, ContentID, HTMLSnippet)
    {
        this.ElementReference = new CDS.Private.ContentInfo.ElementReference();
        this.ElementReference.ID = ContentID;
        this.ElementReference.ElementID = "CDS.ContentInfoPopupButton_" + CDS.Private.ContentInfoPopupButton.ReferenceCounter++;
        this.ElementReference.ElementReference = document.getElementById(this.ElementReference.ElementID);
        this.ElementReference.ElementParameter = null;
        var param = CDS.Private.CreateParamA_S(null,14);
        param = CDS.Private.CreateParamII_CI_V(param);
        param = CDS.Private.CreateParamSI_GL(param);
        param = CDS.Private.CreateParamPIM_PIMS_PIF_PIC(param);
        
        this.ElementReference.ElementReference = document.getElementById(this.ElementReference.ElementID);
        if(this.ElementReference.ElementReference == null)
        {
            if(HTMLSnippet == null) { HTMLSnippet = "More Information..."; }
            document.write("<div id='" + this.ElementReference.ElementID + "' class='CDS_ProductInfoPopupButton' onclick='CDS.Private.ContentInfoPopupButton.ShowContentWindow(\"" + ContentID + "\", event, \"" + param + "\")' style='display:inline;visibility:hidden;'>" + HTMLSnippet + "</div>");
            this.ElementReference.ElementReference = document.getElementById(this.ElementReference.ElementID);
        }
        CDS.Private.ContentInfoPopupButton.References.push(this.ElementReference);
        
        needDelayedShow = (CDS.Private.ContentInfo.Dictionary == null || CDS.Private.ContentInfoPopupButton.ReferenceCounter == 1);
        
        CDS.Private.ContentInfo.GetContentInfo(ContentID);
        if(needDelayedShow)
            CDS.Private.ContentInfoPopupButton.CheckStatus();
        else if(CDS.Private.ContentInfoPopupButton.DataLoaded == true)
            CDS.Private.ContentInfoPopupButton.ShowContentForLoadedItems();
    }
    
    CDS.Private.ContentInfoPopupButton.DataLoaded = false;
    CDS.Private.ContentInfoPopupButton.ReferenceCounter = 0;
    CDS.Private.ContentInfoPopupButton.References = new Array();
    
    CDS.Private.ContentInfoPopupButton.CheckStatus = function()
    {
      if(CDS.Private.ContentInfo.Dictionary == null
        || CDS.Private.ContentInfo.Dictionary == "pending")
      {
         setTimeout(CDS.Private.ContentInfoPopupButton.CheckStatus, CDS.Private.gTimeOut);
         return false;
      }
      
      if(CDS.Private.ContentInfoPopupButton.References.length < 1)
      {
         return false;
      }
      
      //setTimeout(CDS.Private.ContentInfoPopupButton.ShowContentForLoadedItems, CDS.Private.gTimeOut);
      CDS.Private.ContentInfoPopupButton.ShowContentForLoadedItems();
      CDS.Private.ContentInfoPopupButton.DataLoaded = true;
    }
    
    CDS.Private.ContentInfoPopupButton.ShowContentForLoadedItems = function ()
    {
        if(CDS.Private.ContentInfo.Dictionary != null
          && CDS.Private.ContentInfo.Dictionary != "pending")
        {
            for(this.InlineReference in CDS.Private.ContentInfoPopupButton.References)
            {
                if(typeof CDS.Private.ContentInfoPopupButton.References[this.InlineReference] == 'function')
                  continue;
                
                if(CDS.Private.ContentInfo.GetContentByContentAlias(CDS.Private.ContentInfoPopupButton.References[this.InlineReference].ID) != null)
                {
                    CDS.Private.ContentInfoPopupButton.Show(CDS.Private.ContentInfoPopupButton.References[this.InlineReference]);
                    delete CDS.Private.ContentInfoPopupButton.References[this.InlineReference];
                }
            }
            
            for (var i in CDS.Private.ContentInfoPopupButton.References)
            {
                if(typeof CDS.Private.ContentInfoPopupButton.References[i] == 'function')
                  continue;
                while(typeof(CDS.Private.ContentInfoPopupButton.References[i]) == 'undefined' && i < CDS.Private.ContentInfoPopupButton.References.length)
                    CDS.Private.ContentInfoPopupButton.References.splice(i,1);
            }
        }
        else
        {
            //DDD: Needs some more attention because this happened        
            //alert("CDS.Private.ContentInfo.Dictionary = null or pending");
        }
    }

    CDS.Private.ContentInfoPopupButton.Show = function (ElementReference) {
        this.PopupButtonReference = ElementReference.ElementReference;
        if(this.PopupButtonReference != null)
            this.PopupButtonReference.style.visibility='visible';
    }
    
    CDS.Private.ContentInfoPopupButton.ShowContentWindow = function(ContentAlias,EventReference,Parameter)
    {
        retShowHide=false; 
        micrositeInfo = CDS.Private.ContentInfo.GetContentByContentAlias(ContentAlias);
        //debugger;
        if(micrositeInfo != null)
        {
           itemGUID = CDS.Private.ContentInfo.GetContentIDByContentAlias(ContentAlias);
           Parameter += "&IG=" + itemGUID;
           width = micrositeInfo.width;
           height = micrositeInfo.height; 
           url = CDS.Private.gContentBaseURL + micrositeInfo.url + Parameter; 
           url = CDS.Private.CreateParamCB(url);
           retShowHide = CDS_Window_show_hide_box(null, micrositeInfo.title, url, width, height, "", 1);
        }
        return retShowHide;
    }

//DDD-ContentInfo
    CDS.Private.ContentInfo = function () {}
    CDS.Private.ContentInfo.ElementReference = function () {
        this.ID;
        this.ElementID;
        this.ElementReference;
        this.ElementParameter;
    }
    CDS.Private.ContentInfo.Dictionary = null;
    CDS.Private.ContentInfo.GetContentInfo = function (ContentAlias)
    {
        if(CDS.Private.ContentInfo.Dictionary == null)
        {
            CDS.Private.ContentInfo.Dictionary = "pending";
            var param = CDS.Private.CreateParamA_S(null,13);
            param = CDS.Private.CreateParamII_CI_V(param);
            param = CDS.Private.CreateParamSI_GL(param);
            param = CDS.Private.CreateParamPI(param);
            param = CDS.Private.CreateParamPIM_PIMS_PIF_PIC(param);
            param = CDS.Private.CreateParamCB(param);
            this.request = CDS.Private.gProductInfoDirectoryURL + CDS.Private.gGeoLang + "/" + "Contents.json" + param;
            this.json = new CDS.Private.JSON(this.request);
            this.json.buildScriptTag();
            this.json.addScriptTag();
        }
    }
    
    CDS.Private.ContentInfo.Callback = function(callbackdata)
    {
        CDS.Private.ContentInfo.Dictionary = callbackdata;
    }
    
    CDS.Private.ContentInfo.GetContentByContentAlias = function (ContentAlias)
    {
        //this.alias = ContentAlias.replace(/\W/gi, '').toLowerCase();
        this.alias = ContentAlias.toLowerCase();
        this.ContentInfo = null;
        if(typeof(CDS.Private.ContentInfo.Dictionary[this.alias]) == 'object')
        {
            this.ContentInfo = CDS.Private.ContentInfo.Dictionary[this.alias];
        }
        else
        {
            this.ContentInfo = CDS.Private.ContentInfo.Dictionary[CDS.Private.ContentInfo.Dictionary[this.alias]];
        }
        return this.ContentInfo;
    }
    
    CDS.Private.ContentInfo.GetContentIDByContentAlias = function (ContentAlias)
    {
        //this.alias = ContentAlias.replace(/\W/gi, '').toLowerCase();
        this.alias = ContentAlias.toLowerCase();
        this.ContentID = null;
        if(typeof(CDS.Private.ContentInfo.Dictionary[this.alias]) == 'object')
        {
            this.ContentID = this.alias.toUpperCase();
        }
        else
        {
            this.ContentID = CDS.Private.ContentInfo.Dictionary[this.alias];
        }
        return this.ContentID.toUpperCase();
    }
    
//DDD-ProductInfo
    CDS.Private.ProductInfo = function () {}
    CDS.Private.ProductInfo.ElementReference = function () {
        this.ID;
        this.ElementID;
        this.ElementReference;
        this.ElementParameter;
    }
    
    CDS.Private.ProductInfo.Dictionary = null;
    CDS.Private.ProductInfo.GetProductInfo = function (ProductID)
    {
        if(CDS.Private.ProductInfo.Dictionary == null)
        {
            CDS.Private.ProductInfo.Dictionary = "pending";
            var param = CDS.Private.CreateParamA_S(null,3);
            param = CDS.Private.CreateParamII_CI_V(param);
            param = CDS.Private.CreateParamSI_GL(param);
            param = CDS.Private.CreateParamPI(param);
            param = CDS.Private.CreateParamPIM_PIMS_PIF_PIC(param);
            param = CDS.Private.CreateParamCB(param);
            this.request = CDS.Private.gProductInfoDirectoryURL + CDS.Private.gGeoLang + "/" + "Products.json" + param;
            this.json = new CDS.Private.JSON(this.request);
            this.json.buildScriptTag();
            this.json.addScriptTag();
        }
    }
    
    CDS.Private.ProductInfo.Callback = function(callbackdata)
    {
        CDS.Private.ProductInfo.Dictionary = callbackdata;
    }
    
    CDS.Private.ProductInfo.GetProductByProductID = function (ProductID)
    {
        this.sku = ProductID.replace(/\W/gi, '').toLowerCase();
        this.ProductInfo = null;
        if(typeof(CDS.Private.ProductInfo.Dictionary[this.sku]) == 'object')
        {
            this.ProductInfo = CDS.Private.ProductInfo.Dictionary[this.sku];
        }
        else
        {
            this.ProductInfo = CDS.Private.ProductInfo.Dictionary[CDS.Private.ProductInfo.Dictionary[this.sku]];
        }
        return this.ProductInfo;
    }
    
    CDS.Private.ProductInfo.ReferenceCounter = 0;
    CDS.Private.ProductInfo.ShowProductInfoWindow = function(obj, URL, Title, Height, Width, DisplayMode)
    {
        CDS.Private.ProductInfoPopup.Hide();

        
        var viewPortWidth = CDS.Private.Utility.windowState.getWidth();
        var viewPortHeight = CDS.Private.Utility.windowState.getHeight();
        var horizontalScroll = CDS.Private.Utility.windowState.getScrollX();
        var verticalScroll = CDS.Private.Utility.windowState.getScrollY();

        var hPos = Math.round((viewPortWidth - Width)/2);
        var vPos = Math.round((viewPortHeight - Height)/2);
        //var hPos = Math.round(horizontalScroll + ((viewPortWidth - Width)/2));
        //var vPos = Math.round(verticalScroll + ((viewPortHeight -Height)/2));
        hPos = (hPos < 0) ? 0:hPos;
        vPos = (vPos < 0) ? 0:vPos;
        URL = CDS.Private.CreateParamCB(URL);
        CDS.Private.ProductInfo.ReferenceCounter++;
        retShowHide = CDS_Window_show_hide_box(obj, Title, URL, Height, Width, "", DisplayMode);
        return retShowHide;
    }
    
//DDD-JSON
    CDS.Private.JSON=function(fullUrl) {
        // derived from http://theurer.cc/code/jsonSamples/jsr_class.js
        this.fullUrl = fullUrl;
        this.noCacheIE = "";
        this.headLoc = document.getElementsByTagName("head").item(0);
        // generate a unique script tag id
        this.scriptId = 'CDSJscriptId' + CDS.Private.JSON.scriptCounter++;            
    };
    
    CDS.Private.JSON.prototype = {
        
        // static script ID counter
        //scriptCounter: 1,
        
        buildScriptTag: function()
        {
            //create the script tag
            this.scriptObj = document.createElement("script");
            
            // Add script object attributes
            this.scriptObj.setAttribute("type", "text/javascript");
            this.scriptObj.setAttribute("src", this.fullUrl + this.noCacheIE);
            this.scriptObj.setAttribute("id", this.scriptId);
        },
        
        removeScriptTag: function()
        {
            // destroy the script tag
            this.headLoc.removeChild(this.scriptObj);
        },
        
        addScriptTag: function()
        {
            // create the script tag
            this.headLoc.appendChild(this.scriptObj);
        }
    };
    
    CDS.Private.JSON.scriptCounter=0;

//DDD-JSONT
    //jsonT based on http://goessner.net/articles/jsont/
    /*	This work is licensed under Creative Commons GNU LGPL License.
    License: http://creativecommons.org/licenses/LGPL/2.1/
    Version: 0.9
    Author:  Stefan Goessner/2006
    Web:     http://goessner.net/ 
    */
    CDS.Private.JSONT = function(self, rules) {
        var T = {
            output: false,
            init: function() {
                for (var rule in rules)
                    if (rule.substr(0,4) != "self")
                        rules["self."+rule] = rules[rule];
                return this;
            },
            apply: function(expr) {
                var trf = function(s){ return s.replace(/{([A-Za-z0-9_\$\.\[\]\'@\(\)]+)}/g, 
                      function($0,$1){return T.processArg($1, expr);})},
                x = expr.replace(/\[[0-9]+\]/g, "[*]"), res;
                if (x in rules) {
                    if (typeof(rules[x]) == "string")
                        res = trf(rules[x]);
                    else if (typeof(rules[x]) == "function")
                res = trf(rules[x](eval(expr)).toString());
                }
                else 
                    res = T.eval(expr);
                return res;
            },
            processArg: function(arg, parentExpr) {
                var expand = function(a,e){return (e=a.replace(/^\$/,e)).substr(0,4)!="self" ? ("self."+e) : e; },
                res = "";
                T.output = true;
                if (arg.charAt(0) == "@")
                    res = eval(arg.replace(/@([A-za-z0-9_]+)\(([A-Za-z0-9_\$\.\[\]\']+)\)/, 
                        function($0,$1,$2){return "rules['self."+$1+"']("+expand($2,parentExpr)+")";}));
                else if (arg != "$")
                    res = T.apply(expand(arg, parentExpr));
                else
                    res = T.eval(parentExpr);
                T.output = false;
                return res;
            },
            eval: function(expr) {
                var v = eval(expr), res = "";
                if (typeof(v) != "undefined") {
                    if (v instanceof Array) {
                        for (var i=0; i<v.length; i++)
                            if (typeof(v[i]) != "undefined")
                                res += T.apply(expr+"["+i+"]");
                    }
                    else if (typeof(v) == "object") {
                        for (var m in v)
                            if (typeof(v[m]) != "undefined")
                                res += T.apply(expr+"."+m);
                    }
                    else if (T.output)
                        res += v;
                }
                return res;
            }
        }
        return T.init().apply("self");
    }
    
//DDD-IFrameManager     
// Original example at http://geekswithblogs.net/rashid/archive/2007/01/13/103518.aspx
//var FrameManager =
//{
//    currentFrameId : '',
//    currentFrameHeight : 0,
//    lastFrameId : '',
//    lastFrameHeight : 0,
//    resizeTimerId : null,

//    init : function()
//    {
//        if (FrameManager.resizeTimerId == null)
//        {
//            FrameManager.resizeTimerId = window.setInterval(FrameManager.resizeFrames, 500);
//        }
//    },

//    resizeFrames : function()
//    {
//        FrameManager.retrieveFrameIdAndHeight();

//        if ((FrameManager.currentFrameId != FrameManager.lastFrameId) ||
//            (FrameManager.currentFrameHeight != FrameManager.lastFrameHeight))
//        {
//            var iframe = document.getElementById(FrameManager.currentFrameId.toString());

//            if (iframe == null) return;

//            iframe.style.height = FrameManager.currentFrameHeight.toString() + "px";

//            FrameManager.lastFrameId = FrameManager.currentFrameId;
//            FrameManager.lastFrameHeight = FrameManager.currentFrameHeight;
//            //window.location.hash = '';
//        }
//    },

//    retrieveFrameIdAndHeight : function()
//    {
//        if (window.location.hash.length == 0) return;

//        var hashValue = window.location.hash.substring(1);

//        if ((hashValue == null) || (hashValue.length == 0)) return;

//        var pairs = hashValue.split('&');

//        if ((pairs != null) && (pairs.length > 0))
//        {
//            for(var i = 0; i < pairs.length; i++)
//            {
//                var pair = pairs[i].split('=');

//                if ((pair != null) && (pair.length > 0))
//                {
//                    if (pair[0] == 'frameId')
//                    {
//                        if ((pair[1] != null) && (pair[1].length > 0))
//                        {
//                            FrameManager.currentFrameId = pair[1];
//                        }
//                    }
//                    else if (pair[0] == 'height')
//                    {
//                        var height = parseInt(pair[1]);

//                        if (!isNaN(height))
//                        {
//                            FrameManager.currentFrameHeight = height;
//                            FrameManager.currentFrameHeight += 15;
//                        }
//                    }
//                }
//            }
//        }
//    },

//    registerFrame : function(frame)
//    {
//        var currentLocation = location.href;
//        var hashIndex = currentLocation.indexOf('#');

//        if (hashIndex > -1)
//        {
//            currentLocation = currentLocation.substring(0, hashIndex);
//        }
//        
//        frame.contentWindow.location = frame.src + '&frameId=' + encodeURIComponent(frame.id) + '#' + currentLocation;
//    }
//};

//window.setTimeout(FrameManager.init, 300);

}
