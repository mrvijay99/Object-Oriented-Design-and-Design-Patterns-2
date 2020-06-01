//
//  HeatIndexDisplay.cpp
//  Observer Pattern
//
//  Created by Abhinay Reddyreddy on 2/14/18.
//  Copyright © 2018 Brian Arnold. All rights reserved.
//
#include <iostream>
#include "HeatIndexDisplay.hpp"
namespace wf {
  HeatIndexDisplay::HeatIndexDisplay(const std::shared_ptr<Subject>& weatherData)
  : heatIndex(0.0f)
  , weatherData(weatherData)
  {
    token = weatherData->registerObserver(std::bind(&HeatIndexDisplay::update, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
  }
  
  HeatIndexDisplay::~HeatIndexDisplay()
  {
    weatherData->removeObserver(token);
  }
  
  void HeatIndexDisplay::update(float t, float rh, float pressure) {
    heatIndex = computeHeatIndex(t, rh);
    display();
  }
  
  float HeatIndexDisplay::computeHeatIndex(float t, float rh) const {
    float index = (float)((16.923 + (0.185212 * t) + (5.37941 * rh) - (0.100254 * t * rh)
                           + (0.00941695 * (t * t)) + (0.00728898 * (rh * rh))
                           + (0.000345372 * (t * t * rh)) - (0.000814971 * (t * rh * rh)) +
                           (0.0000102102 * (t * t * rh * rh)) - (0.000038646 * (t * t * t)) + (0.0000291583 *
                                                                                               (rh * rh * rh)) + (0.00000142721 * (t * t * t * rh)) +
                           (0.000000197483 * (t * rh * rh * rh)) - (0.0000000218429 * (t * t * t * rh * rh)) +
                           0.000000000843296 * (t * t * rh * rh * rh)) -
                          (0.0000000000481975 * (t * t * t * rh * rh * rh)));
    return index;
  }
  
  void HeatIndexDisplay::display() const {
    std::cout << "Heat index is " << heatIndex << std::endl;
  }
}
