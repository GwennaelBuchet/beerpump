'use strict';

var controllers = angular.module('BeerApp.controllers', []);

var app = angular.module('BeerApp', ['ngWebsocket',
    'BeerApp.controllers'
]);