if (typeof(CDSBE) == 'undefined')
{
   var CDSBE = {
   HostName: "http://content.cdsbe.com",
   //HostName: "http://localhost:4040",
   //HostName: "",
   ClientID: "MWD001",
   Version: 1,
   
   InstanceID: null,
   BaseURL: null,
   VersionBaseURL: null,
   CoreBaseURL: null,
   SharedBaseURL: null,
   ScriptBaseURL: null,
   CssBaseURL: null,
   ImagesBaseURL: null,
   JsonTemplateBaseURL: null,
   JsonBaseURL: null,
   ContentBaseURL: null,
   IsHttps: 0,
   ScriptTagStart: " <script type='text/javascript' src='",
   ScriptTagEnd: "'></script>",
   SyndicatorID: null,
   CreateRandom: function(){
      do
      {
         result = Math.random();
      }
      while(result == 0 || result == 1)
      return result.toString().substring(2);
   },
   Initialize: function(){
      CDSBE.InstanceID = CDSBE.CreateRandom(); 
      if(location.href.substr(0,5) == "https")
      {
         CDSBE.HostName = CDSBE.HostName.replace("http","https");
         CDSBE.IsHttps = 1;
      } 
      CDSBE.BaseURL = CDSBE.HostName + "/" + CDSBE.ClientID + "/";
      CDSBE.VersionBaseURL = CDSBE.BaseURL + CDSBE.Version + "/";
      CDSBE.CoreBaseURL = CDSBE.VersionBaseURL;
      CDSBE.SharedBaseURL = CDSBE.CoreBaseURL + "shared/";
      CDSBE.ScriptBaseURL = CDSBE.SharedBaseURL;
      CDSBE.CssBaseURL = CDSBE.SharedBaseURL + "_css/";
      CDSBE.ImagesBaseURL = CDSBE.SharedBaseURL + "_images/";
      CDSBE.JsonTemplateBaseURL = CDSBE.SharedBaseURL;
      CDSBE.JsonBaseURL = CDSBE.VersionBaseURL + "json/";
      CDSBE.ContentBaseURL = CDSBE.BaseURL + "content/";
   },
   LoadApiComponents: function(SyndicatorID){
      var scripts = document.getElementsByTagName("script");
      if(SyndicatorID == null || SyndicatorID == "")
      {
         CDSBE.SyndicatorID="";
         var searchText = "CDS.core.js?SyndicatorID=";
         var index = -1;
         for(var i=0; i<scripts.length;i++)
         {
           index=scripts[i].src.indexOf(searchText);
           if(index > -1)
           {
              CDSBE.SyndicatorID = scripts[i].src.substr(index + searchText.length);
              break;
           }
         }
      } 
      else
      {
         CDSBE.SyndicatorID = SyndicatorID;
      }
      
      //CDSBE.LoadScriptFile("CDS.aswindow.js", CDSBE.CreateRandom());
      //CDSBE.LoadScriptFile("CDS.api.js", CDSBE.CreateRandom());
      document.write(CDSBE.ScriptTagStart + CDSBE.ScriptBaseURL + "CDS.aswindow.js" + CDSBE.ScriptTagEnd);
      document.write(CDSBE.ScriptTagStart + CDSBE.ScriptBaseURL + "CDS.api.js" + CDSBE.ScriptTagEnd);
   },
   LoadScriptFile: function(fileName, cacheBust){
      var cdsbeCoreParam = "?A=1" + "&S=" + CDSBE.IsHttps 
            + "&II=" + CDSBE.InstanceID + "&CI=" 
            + CDSBE.ClientID + "&V=" + CDSBE.Version 
            + "&SI=" + CDSBE.SyndicatorID + "&CB=" + cacheBust;
      document.write(CDSBE.ScriptTagStart + CDSBE.ScriptBaseURL + fileName + cdsbeCoreParam + CDSBE.ScriptTagEnd);
   }
   };
   
   CDSBE.Initialize();
   CDSBE.LoadApiComponents();
   
   function cdsInitialize(SyndicatorID,GeoLang)
   {
      CDSBE.SyndicatorID = SyndicatorID;
      CDS.SyndicatorID = SyndicatorID;
      
      if(GeoLang != null && GeoLang != "")
      {
         CDS.GeoLang = Geolang;
      }
      
      CDSBE.LoadScriptFile("CDS.postinit.js", CDSBE.InstanceID);
   }
}
