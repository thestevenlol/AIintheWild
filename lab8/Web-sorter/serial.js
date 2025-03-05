// Dr Oisin Cawley SETU 2024
// This version is mostly a copy from the Google Tiny Sorter Example: 
// https://experiments.withgoogle.com/tiny-sorter/view
// However their version of serial.js did not work for me since it was harcoding the device interfaces.
// A better version was availbale at https://webusb.github.io/arduino/demos/serial.js
// Here they iterate through the interfaces to find the correct one.
// That piece of iteration and the related modifications have been updated into this version.

(function() {
  'use strict';
// Oisin Feb 2025
// Following 2 lines has been deprecated:
//  document.addEventListener('DOMNodeInserted', event => {
//    let connectButton = document.querySelector("#connect");
// Replaced with a MutationObserver

  // Change from let port = null to window.port = null to make it global
  window.port = null; // Make port globally accessible

  const observer = new MutationObserver(mutations => {
    for (let mutation of mutations) {
      if (mutation.type === 'childList') {
        let connectButton = document.querySelector("#connect");
        if (connectButton) {
          console.log("Connect button found!");

          function connect() {
            console.log("Attempting to connect to Arduino...");
            window.port.connect().then(() => {  // Use window.port instead of port
              console.log("Arduino connection established successfully!");
              connectButton.textContent = 'DISCONNECT';

              window.port.onReceive = data => {  // Use window.port instead of port
                let textDecoder = new TextDecoder();
                console.log("Data received from Arduino:", textDecoder.decode(data));
              };
              window.port.onReceiveError = error => {  // Use window.port instead of port
                console.error("Error receiving data from Arduino:", error);
              };
            }).catch(error => {
              console.error("Connection error: ", error);
            });
          }

          connectButton.addEventListener('click', function() {
            console.log("Connect button clicked");
            if (window.port) {  // Use window.port instead of port
              console.log("Disconnecting from Arduino...");
              window.port.disconnect();  // Use window.port instead of port
              connectButton.textContent = 'CONNECT ARDUINO';
              window.port = null;  // Use window.port instead of port
              console.log("Disconnected from Arduino");
            } else {
              console.log("Requesting Arduino port...");
              serial.requestPort().then(selectedPort => {
                console.log("Arduino port selected:", selectedPort);
                window.port = selectedPort;  // Use window.port instead of port
                connect();
              }).catch(error => {
                console.error("Port request failed:", error);
              });
            }
          });

          observer.disconnect(); // Stop observing once button is found and handled
          break; // Stop further iteration
        }
      }
    }
  });

  const targetNode = document.body;
  const config = { childList: true, subtree: true };

  observer.observe(targetNode, config);
})();



// From https://github.com/webusb/arduino/blob/gh-pages/demos/serial.js
var serial = {};

(function() {
  'use strict';

  serial.getPorts = function() {
    return navigator.usb.getDevices().then(devices => {
      console.log(devices);
      return devices.map(device => new serial.Port(device));
    });
  };

  serial.requestPort = function() {
    const filters = [
      { 'vendorId': 0x2341, 'productId': 0x8036 },
      { 'vendorId': 0x2341, 'productId': 0x8037 },
      { 'vendorId': 0x2341, 'productId': 0x804d },
      { 'vendorId': 0x2341, 'productId': 0x804e },
      { 'vendorId': 0x2341, 'productId': 0x804f },
      { 'vendorId': 0x2341, 'productId': 0x8050 },
    ];
    return navigator.usb.requestDevice({ 'filters': filters }).then(
      device => new serial.Port(device)
    );
  }

  serial.Port = function(device) {
    this.device_ = device;
	//OC Edit here
    this.interfaceNumber_ = 2;  // original interface number of WebUSB Arduino demo
    this.endpointIn_ = 5;       // original in endpoint ID of WebUSB Arduino demo
    this.endpointOut_ = 4;      // original out endpoint ID of WebUSB Arduino demo
  };

  serial.Port.prototype.connect = function() {
    let readLoop = () => {
      this.device_.transferIn(5, 64).then(result => {
        this.onReceive(result.data);
        readLoop();
      }, error => {
        this.onReceiveError(error);
      });
    };

    console.log("Starting device connection process...");
    //OC Edit below
    return this.device_.open()
        .then(() => {
          console.log("Device opened successfully");
          if (this.device_.configuration === null) {
            console.log("No configuration selected, selecting configuration 1");
            return this.device_.selectConfiguration(1);
          }
        })
.then(() => {
          console.log("Finding interface for Arduino communication");
          var configurationInterfaces = this.device_.configuration.interfaces;
          console.log("Found", configurationInterfaces.length, "interfaces");
          
          configurationInterfaces.forEach((element, index) => {
            console.log(`Examining interface ${index}: ${element.interfaceNumber}`);
            element.alternates.forEach((elementalt, altIndex) => {
              console.log(`  Alternate ${altIndex} - class: ${elementalt.interfaceClass}`);
              if (elementalt.interfaceClass==0xff) {
                console.log(`  Found matching interface: ${element.interfaceNumber}`);
                this.interfaceNumber_ = element.interfaceNumber;
                elementalt.endpoints.forEach((elementendpoint, epIndex) => {
                  console.log(`    Endpoint ${epIndex}: ${elementendpoint.direction}, number: ${elementendpoint.endpointNumber}`);
                  if (elementendpoint.direction == "out") {
                    this.endpointOut_ = elementendpoint.endpointNumber;
                    console.log(`    Setting OUT endpoint to ${this.endpointOut_}`);
                  }
                  if (elementendpoint.direction=="in") {
                    this.endpointIn_ = elementendpoint.endpointNumber;
                    console.log(`    Setting IN endpoint to ${this.endpointIn_}`);
                  }
                })
              }
            })
          })
        })
        .then(() => this.device_.claimInterface(this.interfaceNumber_))
        .then(() => this.device_.selectAlternateInterface(this.interfaceNumber_, 0))
        // The vendor-specific interface provided by a device using this
        // Arduino library is a copy of the normal Arduino USB CDC-ACM
        // interface implementation and so reuses some requests defined by
        // that specification. This request sets the DTR (data terminal
        // ready) signal high to indicate to the device that the host is
        // ready to send and receive data.
        .then(() => this.device_.controlTransferOut({
            'requestType': 'class',
            'recipient': 'interface',
            'request': 0x22,
            'value': 0x01,
            'index': this.interfaceNumber_}))
        .then(() => {
          readLoop();
        });
  };

  serial.Port.prototype.disconnect = function() {
    return this.device_.controlTransferOut({
            'requestType': 'class',
            'recipient': 'interface',
            'request': 0x22,
            'value': 0x00,
            'index': this.interfaceNumber_}) //OC Edit here
        .then(() => this.device_.close());
  };

  serial.Port.prototype.send = function(data) {
    console.log(`Sending data to Arduino via endpoint ${this.endpointOut_}:`, data);
    return this.device_.transferOut(this.endpointOut_, data)
      .then(result => {
        console.log("Data sent successfully:", result);
        return result;
      })
      .catch(error => {
        console.error("Error sending data to Arduino:", error);
        throw error;
      });
  };

  serial.Port.prototype.receive = function(data) {
    return this.device_.transferIn(this.endpointIn_, data); //OC Edit here
  };

})();

