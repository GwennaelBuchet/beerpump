'use strict';


controllers.controller('beerController', function ($scope, $websocket) {
        $scope.drinker = {
            "name": "Gwen",
            "quantity": 0,
            "quantityMax": 2,
            "percent": 0
        };

        $scope.updateDrinker = function (drinker) {
            $scope.drinker.name = drinker.name;
            $scope.drinker.quantity = drinker.quantity;
            $scope.drinker.quantityMax = drinker.quantityMax;
            $scope.drinker.percent = 100 * drinker.quantity / drinker.quantityMax;

            $scope.$apply();
        };

        var ws = $websocket.$new("ws://" + window.location.hostname + ":8081");

        ws.$on('$open',
            function () {
                console.log("Connection opened");
            }
        ).$on('$message',
            function (message) { // it listents for 'incoming event'
                $scope.updateDrinker(message);
            }
        );

    }
);
