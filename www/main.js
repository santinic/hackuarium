angular.module('app', [])
    .controller('MainCtrl', function ($scope, $http, $timeout) {

        $scope.fishes = [0, 1];
        $scope.currentFish = 0;
        $scope.currentDuration = 500;
        $scope.actions = ['Flap', 'Forward', 'Dive', 'Rise'];
        $scope.showWebcam = true;

        $scope.selectFish = function (index) {
            $scope.currentFish = index;
        };

        $scope.command = function (cmd) {
            var url = '/arduino/fish-cmd/' + $scope.currentFish + '/' + cmd + '/' + $scope.currentDuration;
            $http.get(url);
        };

        $scope.action = function (act) {
            var url = '/arduino/fish-action/' + $scope.currentFish + '/' + act;
            $http.get(url);
        };

        $scope.keyboard = function ($event) {
            //console.log($event.keyCode);
            $timeout(function () {
                var match = {
                    '38': 'Up', '37': 'Left', '39': 'Right', '40': 'Down',
                    '70': 'Flap', '68': 'Dive', '82': 'Rise'
                };
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
    })
    .controller('WebcamCtrl', function ($scope) {
        $scope.currentImg = 0;
        var src = "https://london.hackspace.org.uk/members/camera.php?id=19";

        function replaceWebcamImg() {
            var nextImg = ($scope.currentImg + 1) % 2;
            //console.log('current', $scope.currentImg + ', loading #webcam'+nextImg);

            $('#webcam'+nextImg).unbind().attr('src', src).load(function() {
                //console.log('loaded!')
                $scope.currentImg = nextImg;
                $scope.$digest();
                replaceWebcamImg();
            });
        }
        replaceWebcamImg();

    });