function ReqAddNode() {
    // var operations = document.getElementsByClassName('.operations'); 
    // operations.classList.toggle("add_node");
    // operations.classList.toggle("add_edge");     

      var nodeNameValue = document.getElementById("node_name_ID").value; 
      var xValue = document.getElementById("x_ID").value;
      var yValue = document.getElementById("y_ID").value;
      
      var xhr = new XMLHttpRequest();
      xhr.open('POST', 'http://localhost:8080/', true);
      
      xhr.onreadystatechange = function() {
        if (this.readyState != 4) return;
      }
      
      xhr.send("1 " + nodeNameValue + " " + xValue + " " + yValue + " @end");
}

function ReqAddEdge() {      

    var start = document.getElementById("start_ID").value;
    var end = document.getElementById("end_ID").value;
    
    var xhr = new XMLHttpRequest();
    xhr.open('POST', 'http://localhost:8080/', true);
    
    xhr.onreadystatechange = function() {
      if (this.readyState != 4) return;
    }
    
    xhr.send("2 " + start + " " + end + " @end");
}

function ReqShowPath() { 
  
    document.location.href = "hide_path.html";

    var start = document.getElementById("start_path_ID").value;
    var end = document.getElementById("end_path_ID").value;

    var xhr = new XMLHttpRequest();
    xhr.open('POST', 'http://localhost:8080/', true);
    
    xhr.onreadystatechange = function() {
      if (this.readyState != 4) return;
    }
    
    xhr.send("3 " + start + " " + end + " @end");
}

function ReqHidePath() {   
  
    document.location.href = "path.html";

    var xhr = new XMLHttpRequest();
    xhr.open('POST', 'http://localhost:8080/', true);
    
    xhr.onreadystatechange = function() {
      if (this.readyState != 4) return;
    }
    
    xhr.send("4 @end");
}

function ReqRemoveEdge() {

    var start = document.getElementById("remove_start_ID").value;
    var end = document.getElementById("remove_end_ID").value;
    
    var xhr = new XMLHttpRequest();
    xhr.open('POST', 'http://localhost:8080/', true);
    
    xhr.onreadystatechange = function() {
      if (this.readyState != 4) return;
    }
    
    xhr.send("5 " + start + " " + end + " @end");
}

function ReqRemoveNode() {

    var start = document.getElementById("remove_node_ID").value;
    
    var xhr = new XMLHttpRequest();
    xhr.open('POST', 'http://localhost:8080/', true);
    
    xhr.onreadystatechange = function() {
      if (this.readyState != 4) return;
    }
    
    xhr.send("6 " + start + " @end");
}

