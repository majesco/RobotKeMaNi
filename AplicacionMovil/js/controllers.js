
angular.module('starter.controllers', ['ngCordova'])

    .controller('DashCtrl', function($scope) {
    
    
    $scope.enableBluetooth  = enableBluetooth;  
    $scope.connectToDevice  = connectToDevice;
    $scope.discover = discover;
    $scope.connectionStatus = "Connect";
    $scope.list =   list;
    $scope.write = write;
    $scope.read =  read;
    $scope.isConnected  = isConnected;
    $scope.controlToggle = true;

    $scope.toggleControl =toggleControl;
    
    function toggleControl(){
        $scope.controlToggle =!$scope.controlToggle;

            $scope.write(5);
    }

    function enableBluetooth() {
        bluetoothSerial.enable(
            function () {
                alert("El Bluetooth está habilitado");
            },
            function () {
                alert("El usuario no habilitó el Bluetooth");
            }
        );
    }

    function connectToDevice(){

        // bluetoothSerial.setDiscoverable(0);
        var macAddress ="20:16:07:25:29:41"
        //  var macAddress="E4:CE:8F:28:95:75";
        bluetoothSerial.connectInsecure(macAddress,

                                        function() {
            // if you get a good Bluetooth serial connection:
            alert("Conectado a la dirección: " + app.macAddress);
            // change the button's name:
            $scope.connectionStatus = "Deconectar";
            // set up a listener to listen for newlines
            // and display any new data that's come in since
            // the last newline:
            bluetoothSerial.subscribe('\n', function (data) {
                alert("Se ha realizado una suscripación a  "+data);
            });
        },
                                        function(error) {
            alert(error);
        }
                                       );
    }

    function suscribe(){
        bluetoothSerial.subscribe('\n', function (data) {
            alert("suscripcion "+data);
        });
    }

    function isConnected(){ 
        bluetoothSerial.isConnected(
            function() {
                alert("El Bluetooth está conectado");
            },
            function() {
                alert("El Bluetooth no está conectado");
            }
        );
    }

    function write (tipo){

        var data;

        if (tipo==0){

            data = new Uint8Array(1);
            data[0] = 0x66; //f (forward)
        }
        if (tipo==1){

            data = new Uint8Array(1);
            data[0] = 0x62; //b (backwards)
        }
        if (tipo==2){
            data = new Uint8Array(1);
            data[0] = 0x30; // r (right)
        }
        if (tipo==3){
            data = new Uint8Array(1);
            data[0] = 0x6c; //l (left)
        }
        if (tipo==4){
            data = new Uint8Array(4);
            data[0] = 0x30;
            data[1] = 0x31;
            data[2] = 0x30;
            data[3] = 0x31;
        }
        if (tipo==5){
            
            if ($scope.controlToggle){
                
                return;
            }
            data = new Uint8Array(1);
            data[0]= 0x6D;
        }


        bluetoothSerial.write(data, console.log("Escritura exitosa"), console.log("Escritura fallida"));    
    }


    function read(){

        bluetoothSerial.read( function (data) {
            if (data ==0x63){   //c  complete{

                alert("Nivel de tanque alto, por favor vaciar el tanque pronto")
            }
            alert("Leido "+data);
        }, alert("Lectura fallida"));
    }


    function discover(){

        bluetoothSerial.discoverUnpaired(function(devices) {
            devices.forEach(function(device) {
                alert("Se encontró al dispositivo "+device.id);
            })
        }, alert("No se ha encontrado ningún dispositivo no emparejado"));
    }

    function list(){ 

        bluetoothSerial.list(function(devices) {
            devices.forEach(function(device) {
                alert("La dirección MAC de este disppositivo es "+device.id);
            })
        },alert("No se ha encontrado ningún dispositivo emparejado"));

    }

});

