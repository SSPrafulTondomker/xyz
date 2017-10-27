$(document).ready(function(){
 document.getElementById('textEditor').contentWindow.document.designMode="on";
 document.getElementById('textEditor').contentWindow.document.close();
 var edit = document.getElementById("textEditor").contentWindow;
 edit.focus();
 $("#bold").click(function(){
  if($(this).hasClass("selected")){
   $(this).removeClass("selected");
  }else{
   $(this).addClass("selected");
  }
  boldIt();
 });
 $("#italic").click(function(){
  if($(this).hasClass("selected")){
   $(this).removeClass("selected");
  }else{
   $(this).addClass("selected");
  }
  ItalicIt();
 });
 $("#fonts").on('change',function(){
  changeFont($("#fonts").val());
 });
 $("#Underline").click(function(){
    if($(this).hasClass("selected")){
   $(this).removeClass("selected");
  }else{
   $(this).addClass("selected");
  }
  UnderlineIt();
 }); 
 $("#stext").click(function(){
  $("#text").hide();
  $("#textEditor").show();
  $("#controls").show()
 });

});
function boldIt(){
 var edit = document.getElementById("textEditor").contentWindow;
 edit.focus();
  edit.document.execCommand("bold", false, "");
  edit.focus();
}
function ItalicIt(){
 var edit = document.getElementById("textEditor").contentWindow;
 edit.focus();
 edit.document.execCommand("italic", false, "");
 edit.focus();
}
function changeFont(font){
 var edit = document.getElementById("textEditor").contentWindow;
 edit.focus();
 edit.document.execCommand("FontName", false, font);
 edit.focus();
}
function UnderlineIt(){
 var edit = document.getElementById("textEditor").contentWindow;
 edit.focus();
 edit.document.execCommand("Underline", false, "");
 edit.focus();
}
setInterval(function(){
 var gyt=$("#textEditor").contents().find("body").html().match(/@/g);
 if($("#textEditor").contents().find("body").html().match(/@/g)>=0){}else{
  $("#text").val($("#textEditor").contents().find("body").html());
 }
 $("#text").val($("#textEditor").contents().find("body").html());
},10);