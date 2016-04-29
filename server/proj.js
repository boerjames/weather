var XMLHttpRequest = require("xmlhttprequest").XMLHttpRequest;
var app = require('http').createServer(handler)
var io = require('socket.io')(app);
var fs = require('fs');

app.listen(8085);

var htmlPage = 'index.html'; // Debian
var soc;
var currentWeather = 'Startup';
var lastQuery;
var tMode = true;
var repeatTime = 60000;



setInterval(updateWeather, repeatTime);


function handler(req, res) {
    //console.log("Opening HTML File");
    fs.readFile(htmlPage, function(err, data) {
        if (err) {
            res.writeHead(500);
            return res.end('Error loading file: ' + htmlPage);
        }
        res.writeHead(200);
        res.end(data);
    });
}

io.on('connection', function (socket) {
  console.log("Connected");
    
    socket.on('LatLng', handleLatLng);
    socket.on('Btn', handleButton);
    soc = socket;
});

function updateWeather(){
    if(currentWeather != 'Startup'){
        //initial location exists
        httpGetAsync(lastQuery);
        
        
        
        
    }
    
    
    
    
}

function handleButton(message){
    console.log("Button Clicked");
    
    if(message == 0){
        console.log("Reset");
        currentWeather = 'Startup';
    }
    if(message == 1){
        console.log("C/F");
        tMode = !tMode;
    }
    if(message == 2){
        console.log("Windspeed");
    }
    
}


function handleLatLng(message){
    //console.log("Latitude: " + message.lat + ", Longitutde: " + message.lng);
    console.log("Right Click Happened");
    var query = "http://api.wunderground.com/api/c9eca004c2ae9eb2/forecast/geolookup/conditions/q/";
    query = query + message.lat + "," + message.lng + ".json";
    lastQuery = query;
    httpGetAsync(query);
}

function httpGetAsync(theUrl)
{
    console.log("Requesting new data from WUnderground");
    
    var xmlHttp = new XMLHttpRequest();
    xmlHttp.onreadystatechange = function() { 
        if (xmlHttp.readyState == 4 && xmlHttp.status == 200)
            handleWUResponse(xmlHttp.responseText);
    };
    xmlHttp.open("GET", theUrl, true); // true for asynchronous 
    xmlHttp.send(null);
}


function handleWUResponse(responseText){
    //console.log("Handling WUnderground response");
    
    JSON.parse(responseText, function(property,value){
        //console.log(property + ": " + value);
        if(property == "weather"){
            /*
            * Clear, Snow, Mostly Cloudy, Partly Cloudy, Rain, Light Rain
            * Thunderstorm, Scattered Clouds
            */
            console.log("W: " + value);
            var wVal = 0;
            switch(value){
                    case "Clear":
                    wVal = 0;
                    break;
                    case "Mostly Cloudy":
                    wVal = 1;
                    break;
                    case "Partly Cloudy":
                    wVal = 2;
                    break;
                    case "Rain":
                    wVal = 3;
                    break;
                    case "Light Rain":
                    wVal = 4;
                    break;
                    case "Thunderstorm":
                    wVal = 5;
                    break;
                    case "Scattered Clouds":
                    wVal = 6;
                    break;
                    case "Overcast":
                    wVal = 7;
                    break;
                    default:
                    wVal = -1;
            }
            
            updateWeatherLEDs(wVal);
            
            currentWeather = value;
        }
        if(property == "temp_f" && tMode){
            console.log("T: " + value);
            updateTemp(parseFloat(value));
        }
        if(property == "temp_c" && !tMode){
            console.log("T: " + value);
            updateTemp(parseFloat(value));
        }
    });
    
}

function updateWeatherLEDs(val){
    if(val != -1){
        console.log("Found Matching Val");
    console.log(val);
    }
    else{
        console.log("Unknown WeatherType found");
    }
    
}

function updateTemp(val){
    if(val < -10){
        val = -10;
    }
    if(val > 110){
        val = 110;
    }
    console.log("Updating TempLEDS");
    console.log(val);
}



