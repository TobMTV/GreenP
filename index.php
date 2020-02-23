<!DOCTYPE html>
<html>
	<head>
		<title> Green Project </title>
		<link rel="shortcut icon" href="http://www.veryicon.com/icon/ico/System/Tea/tea%20plant%20leaf.ico">
		<link href = "css/stile.css" rel = "stylesheet" type = "text/css" />
		<link href="css/font-awesome/font-awesome.css" rel="stylesheet">
  		<link href="css/style.css" rel="stylesheet">
		<script src = "js/jquery.min.js"> </script>
		<script src = "js/ajaxAndFunctions.js"> </script>
		
		<!-- Script per l'effetto del mouse sopra al bottone download -->
		<script>
			$(function() {
				$("#downloadButton").hover(function() {
					$(this).html("<img src = \"img/android2.png\" id =\"downloadImage\" /><br> DOWNLOAD");
				}, function() {
					$(this).html("<img src = \"img/android.png\" id =\"downloadImage\" /><br> DOWNLOAD");
				});
			});
		</script>
		/* Script per la gestione della finestra del video */
			<script>
				var openedVideo = false;
				$(function() {
					$("#headVideo").click(function() {
						if (!openedVideo) {
							$("#videoBox").css("top","0px");
							$("#videoBox").css("bottom","0px");
							$("#headVideo").html("Chiudi video");
							$("#videoBox").css("height","100%");
							$("#videoContainer").css("display","block");
							openedVideo = true;
						}
						else {
							$("#videoBox").css("top","auto");
							$("#videoBox").animate({bottom: "50px"});
							$("#headVideo").html("Apri video");
							$("#videoBox").css("height","0%");
							$("#videoContainer").css("display","none");
							openedVideo = false;
						}
					});
				});
			</script>
	</head>
	
	<body onload = "loop()">
		<!-- Header che contiene il nome del progetto e lo stato -->
		<div id = "header"> 
			<h2> Green project </h2>
			<div id = "statusBox" class = "disabled"> 
				<span id = "statusLabel"> status: </span>
				
				<div id = "status"> </div>
			</div>
		</div>
		
		<!-- Box principale sotto l'header --->
		<div id = "box">
			<!-- Box che contiene il riquadro info e bottoni -->
			<div id = "riquadroDx">
				<div id = "infoBox">
				
					<div id = "temperatura" class = "info">
						<div class = "label">Temperatura</div>
						<div class = "infos" id = "temp"> </div>
					</div>
					
					<div id = "umidita"  class = "info">
						<div class = "label"> Umitid&agrave; </div>
						<div class = "infos" id = "hum"> </div>
					</div>
					
					<div id = "luminosita"  class = "info">
						<div class = "label"> Luminosit&agrave; </div>
						<div class = "infos" id = "lum"> </div>
					</div>
				
				</div> <br><br>
				<div id = "buttonBox">
					<div id = "lampadina"  class = "buttons">
						<div class = "label"> Lampadina </div>
						<input type = "button" name = "autoLamp" value = "auto" id = "autoLampButton" onclick = "autoLampFunction()"/>
						<div class="switch">
            				<input id="lampadinaSwitch" class="cmn-toggle cmn-toggle-round" type="checkbox" onclick = "switchLamp()"> <!-- checked se attivo -->
            				<label for="lampadinaSwitch"></label>
          				</div>
					</div>
					
					<div id = "pompa"  class = "buttons">
						<div class = "label"> Pompa </div>
						<input type = "button" name = "autoPump" value = "auto" id = "autoPumpetButton" onclick = "autoPumpFunction()"/>
						<div class="switch">
            				<input id="pompaSwitch" onclick = "switchPump()" class="cmn-toggle cmn-toggle-round" type="checkbox" name = "pompaSwitch"> <!-- checked se attivo -->
            				<label for="pompaSwitch"></label>
          				</div>
					</div>
				
				</div> <br><br>
			</div>
			
			<div id = "riquadroSx">
				<div id = "logo">
					Benvenuto in <br> GREEN PROJECT
				</div>
				</div>
				<!-- Box che contiene il titolo e il bottone di download -->
				<a href = "android_app.zip">
				<div id = "downloadButton">
					<img src = "img/android.png" id = "downloadImage" />
					<br>
					DOWNLOAD
				</div>
				</a>
			</div>
			
		</div>
		
		<div id = "videoBox">
			<div id = "headVideo"> Apri video</div>
			<div id = "videoContainer">
				<img src = "img/video.jpg" id = "video" />
			</div>
		</div>
		
	</body>
</html>