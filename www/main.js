angular.module('app', [])
    .controller('MainCtrl', function ($scope, $http, $timeout) {

        $scope.fishes = [0, 1];
        $scope.currentFish = 0;
        $scope.currentDuration = 500;
        $scope.actions = ['Flap', 'Forward', 'Dive', 'Rise'];

        $scope.selectFish = function (index) {
            $scope.currentFish = index;
        };

        $scope.command = function (cmd) {
            var url = '/arduino/fish-cmd/' + $scope.currentFish + '/' + cmd + '/' + $scope.currentDuration;
            $http.get(url)
                .success(function (data, status, headers) {
                    console.log(url + ' callback');
                })
                .error(function (data, status, headers) {
                    console.error(url, data);
                });
        };

        $scope.action = function (act) {
            var url = '/arduino/fish-action/' + $scope.currentFish + '/' + act;
            $http.get(url);
        };

        $scope.keyboard = function ($event) {
            $timeout(function () {
                var match = { '38': 'Up', '37': 'Left', '39': 'Right', '40': 'Down'};
                var buttonId = match[$event.keyCode];
                if (buttonId) {
                    var button = $('#' + buttonId);
                    button.toggleClass('clicked').click();
                    $timeout(function() {
                        button.toggleClass('clicked');
                    },200);
                }
            })
        };

    });