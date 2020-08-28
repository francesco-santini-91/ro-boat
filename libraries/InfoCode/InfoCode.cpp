#include "Arduino.h"
#include "InfoCode.h"

InfoCode::InfoCode(string infocode) {
    this->_InfoCode = this->_InfoCode + infocode;
}

bool InfoCode::verify() {
    if(this->_InfoCode.StartsWith("$")) {
        
    }
}

String InfoCode::getParameter() {
    
}