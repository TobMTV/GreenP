/* VARIABILI GLOBALI */
var alertTemp = false;
var autoPumpState = 1;
var autoLampState = 1;
			

function richiestaAJAX(parametri) {
	//console.log(parametri);
	if (window.XMLHttpRequest)
	{
		xmlhttp=new XMLHttpRequest();
	}
	else
	{
		xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
	}
	xmlhttp.onreadystatechange=function()
	{
		if (xmlhttp.readyState==4 && xmlhttp.status==200){
			console.log(xmlhttp.responseText);
			var rText = xmlhttp.responseText;
			var splitResponse = rText.split("-");
			for (var i=0; i < splitResponse.length; i++) {
				var information = splitResponse[i].split(":");
				if (information[1] != "ON" && information[1] != "OFF") {
					if (information[0] == "autoPum") {
						autoPumpState = information[1];
						changeButtonColorPump();
					}
					else if (information[0] == "autoLamp") {
						autoLampState = information[1];
						changeButtonColorLamp();
					}
					else
						document.getElementById(information[0]).innerHTML = information[1];
				}
				else {
					if (information[1] == "ON")
						document.getElementById(information[0]).checked = true;
					else
						document.getElementById(information[0]).checked = false;
				}
			}
		}
	}
	
	xmlhttp.open("GET","http://192.168.2.200?"+parametri,true);
	//xmlhttp.open("GET","file.php",true); //prova con file.php per la dinamicità dello scambio di info
	xmlhttp.send();
	//var arduResponse = xmlhttp.responseText;			
	tempControl();
	statusControl();
	
}
function statusControl(){
var contenuto = document.getElementById("temp").innerHTML;
if(isNaN(contenuto) || contenuto == " ")
$("#statusBox").removeClass().addClass("disabled");
else
$("#statusBox").removeClass().addClass("enabled");
}	
	
			
function changeButtonColorPump() {
	if (autoPumpState == 1)
		document.getElementById("autoPumpetButton").style.background = "green";
	else
		document.getElementById("autoPumpetButton").style.background = "red";
}
function changeButtonColorLamp() {
	if (autoLampState == 1)
		document.getElementById("autoLampButton").style.background = "green";
	else
		document.getElementById("autoLampButton").style.background = "red";
}
		
function loop() {
	setInterval(richiestaAJAX, 1000);
}
			
function tempControl() {
	var tempControl = document.getElementById("temp").innerHTML;
	if (!alertTemp && tempControl > 30) {
		alert("La temperatura e' troppo elevata!");
		$("#temp").css("color","red");
		alertTemp = true;
	}
				
	if (tempControl <= 30) {
		alertTemp = false;
		$("#temp").css("color","black");
	}
				
}
			
function autoPumpFunction() {
	if (autoPumpState == 1)
		autoPumpState = 0;
	else
		autoPumpState = 1;
	richiestaAJAX("autoPump="+autoPumpState);
}	
			
function autoLampFunction() {
	if (autoLampState == 1)
		autoLampState = 0;
	else
		autoLampState = 1;
	richiestaAJAX("autoLamp="+autoLampState);
}	

function switchPump() {
	richiestaAJAX('pump='+document.getElementById('pompaSwitch').checked);
}

function switchLamp() {
	richiestaAJAX('lamp='+document.getElementById('lampadinaSwitch').checked);
}