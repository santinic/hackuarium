
angular.module('app', [])
    .controller('MainCtrl', function($scope, $http, $timeout) {

        $scope.fishes = [0,1];
        $scope.currentFish = 0;
        $scope.currentDuration = 500;

        $scope.selectFish = function(index){
            $scope.currentFish = index;
        };

        $scope.command = function(cmd) {
            var url = '/arduino/fish-cmd/'+$scope.currentFish+'/'+cmd+'/'+$scope.currentDuration;
            $http.get(url)
                .success(function(data, status, headers) {
                    console.log(url+' callback');
                })
                .error(function(data, status, headers) {
                    console.error(url, data);
                });
        };

        $scope.keyboard = function($event) {
            if(['Up', 'Down', 'Left', 'Right'].indexOf($event.keyIdentifier) !== -1) {
                $timeout(function() {
                    document.getElementById($event.keyIdentifier).click();
                });
            }
        };

    });