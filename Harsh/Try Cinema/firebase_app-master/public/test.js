(function(){


  var config = {
    apiKey: "AIzaSyDSSPjvsfugVjFyW3xpw78Bj9rzqbXVB54",
    authDomain: "blog-733f2.firebaseapp.com",
    databaseURL: "https://blog-733f2.firebaseio.com",
    storageBucket: "blog-733f2.appspot.com",
    messagingSenderId: "172802368877"
  };
  firebase.initializeApp(config);
  angular
      .module('TextEditor',['firebase','ngSanitize'])
      
      .controller('MyCtrl',['$scope','$firebaseArray',function($scope,$firebaseArray)
{

  
   $scope.rootref=firebase.database().ref();
   console.log(new Date(Date.now()).toLocaleString());
  $scope.list=$firebaseArray($scope.rootref);
  $scope.addimage=function(url,id)
  {
    if( document.getElementById(id+'image')!=null)
    {
      document.getElementById(id+'image').remove();}
    //dynamically add an image and set its attribute
    var img=document.createElement("img");
    img.src=url;
    img.id=id+"image";
    img.setAttribute("height", "300");
    img.setAttribute("width", "350");
  
    var foo = document.getElementById(id);
    foo.appendChild(img);
}

  
  $scope.show=function(blog){
    
   
    $scope.storageRef = firebase.storage().ref("images/"+blog.$id+".jpg");
    $scope.storageRef.getDownloadURL().then(function(url) {
    console.log(url);
    $scope.addimage(url,blog.$id);
}, function(error) {
  
  
    return false;
})
  }

}
      ] );



}());
