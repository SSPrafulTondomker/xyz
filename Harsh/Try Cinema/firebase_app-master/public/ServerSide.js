(function(){


  // Initialize Firebase
  var config = {
    apiKey: "AIzaSyDSSPjvsfugVjFyW3xpw78Bj9rzqbXVB54",
    authDomain: "blog-733f2.firebaseapp.com",
    databaseURL: "https://blog-733f2.firebaseio.com",
    storageBucket: "blog-733f2.appspot.com",
    messagingSenderId: "172802368877"
  };
  firebase.initializeApp(config);
  angular
  		.module('TextEditor',['firebase'])
  		
  		
  		.controller('MyCtrl',['$scope','$firebaseObject',function($scope,$firebaseObject)
{

	var id=Math.random().toString(16).slice(2);
	 $scope.rootref=firebase.database().ref().child(id);
   
	$scope.object=$firebaseObject($scope.rootref);
	 
$scope.filebutton=document.getElementById('image');
   $scope.filebutton.addEventListener('change',function(e)
{  
  
	 
	$scope.file=e.target.files[0];
    $scope.storageRef = firebase.storage().ref("images/"+id+".jpg");
    $scope.task=$scope.storageRef.put($scope.file);
    $scope.task.on('state_changed',
    	function progress(snapshot)
    	{
    		var per=(snapshot.bytesTransferred/snapshot.totalBytes)*100;
    		document.getElementById('uploader').value=per;
        document.getElementById('info').innerHTML="Wait for image to Upload";
    	},
function error(err)
{
  alert("image not uploaded");
},
function complete(){
  document.getElementById('info').innerHTML=" Image Uploaded";
}

    	);


}
   	);
	
$scope.add=function()
{
	
	$scope.object.title = $scope.title;  
	$scope.object.value=$("#textEditor").contents().find("body").html();
  $scope.object.time=new Date(Date.now()).toLocaleString();
$scope.object.$save().then(function(ref) {
  ref.key===$scope.object.$id; // true
}, function(error) {
  console.log("Error:", error);
  alert("Don't save your Blog empty");
});


}

	
	

}
  		]	);
  
}());
