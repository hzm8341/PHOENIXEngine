// cloud.js

var SnapCloud = new Cloud(
    'http://www.manykit.com/snap/'
);

Cloud.prototype.originalSignup = Cloud.prototype.signup;
Cloud.prototype.signup = function (username, email, callBack, errorCall) {

    var request = new XMLHttpRequest(),
        myself = this;

    var strPath = this.url + 'signup' + '?username='
        + encodeURIComponent(username) + '&email='
        + encodeURIComponent(email);

    try {
        request.open(
            "GET",
            strPath,
            true
        );
        request.setRequestHeader(
            "Content-Type",
            "application/x-www-form-urlencoded"
        );
        request.withCredentials = true;
        request.onreadystatechange = function () {
            if (request.readyState === 4) {
                if (request.responseText) {
                    if (request.responseText.indexOf('ERROR') === 0) {
                        errorCall.call(
                            this,
                            request.responseText,
                            'Signup'
                        );
                    } else {
                        callBack.call(
                            null,
                            request.responseText,
                            'Signup'
                        );
                    }
                } else {
                    errorCall.call(
                        null,
                        myself.url + 'SignUp',
                        localize('could not connect to:')
                    );
                }
            }
        };
        request.send(null);
    } catch (err) {
        errorCall.call(this, err.toString(), 'Snap!Cloud');
    }
};

Cloud.prototype.originalGetPublicProject = Cloud.prototype.getPublicProject;
Cloud.prototype.getPublicProject = function (id, callBack, errorCall) {

};

Cloud.prototype.originalResetPassword = Cloud.prototype.resetPassword;
Cloud.prototype.resetPassword = function (username, callBack, errorCall) {
    var request = new XMLHttpRequest(),
        myself = this;

    var strPath = this.url + 'resetpw' + '?username=' + encodeURIComponent(username);

    try {
        request.open(
            "GET",
            strPath,
            true
        );
        request.setRequestHeader(
            "Content-Type",
            "application/x-www-form-urlencoded"
        );
        request.withCredentials = true;
        request.onreadystatechange = function () {
            if (request.readyState === 4) {
                if (request.responseText) {
                    if (request.responseText.indexOf('ERROR') === 0) {

                        errorCall.call(
                            this,
                            request.responseText,
                            'resetpw failed!'
                        );
                    } else {
                        myself.password = "";

                        callBack.call(
                            null,
                            request.responseText,
                            'resetpw suc!'
                        );
                    }
                } else {
                    errorCall.call(
                        null,
                        myself.url + 'login',
                        localize('could not connect to:')
                    );
                }
            }
        };
        request.send(null);
    } catch (err) {
        errorCall.call(this, err.toString(), 'Snap!Cloud');
    }
};

Cloud.prototype.originalLogin = Cloud.prototype.login;
Cloud.prototype.login = function (
    username,
    password,
    callBack,
    errorCall
) {
    var request = new XMLHttpRequest(),
        myself = this;

    var strPath = this.url + 'login' + '?username='
        + encodeURIComponent(username) + '&password='
        + encodeURIComponent(password);

    try {
        request.open(
            "GET",
            strPath,
            true
        );
        request.setRequestHeader(
            "Content-Type",
            "application/x-www-form-urlencoded"
        );
        request.withCredentials = true;
        request.onreadystatechange = function () {
            if (request.readyState === 4) {
                if (request.responseText) {
                    if (request.responseText.indexOf('ERROR') === 0) {

                        myself.username = "";
                        myself.password = "";

                        errorCall.call(
                            this,
                            request.responseText,
                            'login failed!'
                        );
                    } else {
                        myself.username = username;
                        myself.password = password;

                        callBack.call(
                            null,
                            request.responseText,
                            'login suc!'
                        );
                    }
                } else {
                    errorCall.call(
                        null,
                        myself.url + 'login',
                        localize('could not connect to:')
                    );
                }
            }
        };
        request.send(null);
    } catch (err) {
        errorCall.call(this, err.toString(), 'Snap!Cloud');
    }
};

Cloud.prototype.originalReconnect = Cloud.prototype.reconnect;
Cloud.prototype.reconnect = function (
    callBack,
    errorCall
) {
    if (!(this.username && this.password)) {
        this.message('You are not logged in');
        return;
    }
    this.login(
        this.username,
        this.password,
        callBack,
        errorCall
    );
};

Cloud.prototype.originalSaveProject = Cloud.prototype.saveProject;
Cloud.prototype.saveProject = function (ide, callBack, errorCall) {
}

Cloud.prototype.originalGetProjectList = Cloud.prototype.getProjectList;
Cloud.prototype.getProjectList = function (callBack, errorCall) {
    var myself = this;
    this.reconnect(
        function () {
            myself.callService(
                'getprojectlist',
                function (response, url) {
                    callBack.call(null, response, url);
                    myself.disconnect();
                },
                errorCall
            );
        },
        errorCall
    );
};

Cloud.prototype.originalChangePassword= Cloud.prototype.changePassword;
Cloud.prototype.changePassword = function (
    oldPW,
    newPW,
    callBack,
    errorCall
) {

};

Cloud.prototype.originalLogout = Cloud.prototype.logout;
Cloud.prototype.logout = function (callBack, errorCall) {
    var request = new XMLHttpRequest(),
        myself = this;

    var strPath = this.url + 'logout';

    try {
        request.open(
            "GET",
            strPath,
            true
        );
        request.setRequestHeader(
            "Content-Type",
            "application/x-www-form-urlencoded"
        );
        request.withCredentials = true;
        request.onreadystatechange = function () {
            if (request.readyState === 4) {
                if (request.responseText) {
                    if (request.responseText.indexOf('ERROR') === 0) {

                        myself.username = "";
                        myself.password = "";

                        errorCall.call(
                            this,
                            request.responseText,
                            'login failed!'
                        );
                    } else {
                        myself.username = "";
                        myself.password = "";

                        callBack.call(
                            null,
                            request.responseText,
                            'logout suc!'
                        );
                    }
                } else {
                    errorCall.call(
                        null,
                        myself.url + 'logout',
                        localize('could not connect to:')
                    );
                }
            }
        };
        request.send(null);
    } catch (err) {
        errorCall.call(this, err.toString(), 'Snap!Cloud');
    }
};

Cloud.prototype.originalDisconnect = Cloud.prototype.disconnect;
Cloud.prototype.disconnect = function () {

};

Cloud.prototype.originalCallService = Cloud.prototype.callService;
Cloud.prototype.callService = function (
    serviceName,
    callBack,
    errorCall,
    args
) {
    // both callBack and errorCall are optional two-argument functions
    var request = new XMLHttpRequest(),
        service = serviceName,
        myself = this,
        stickyUrl,
        postDict;

    if (!service) {
        errorCall.call(
            null,
            'service ' + serviceName + ' is not available',
            'API'
        );
        return;
    }
    if (args && args.length > 0) {
        postDict = args;
    }
    try {
        stickyUrl = this.url + service + '?username='
            + encodeURIComponent(this.username) + '&param=' + postDict;
        request.open("POST", stickyUrl, true);
        request.withCredentials = true;
        request.setRequestHeader(
            "Content-Type",
            "application/x-www-form-urlencoded"
        );
        request.setRequestHeader('MioCracker', this.session);
        request.setRequestHeader('SESSIONGLUE', this.route);
        request.onreadystatechange = function () {
            if (request.readyState === 4) {
                var responseList = [];
                if (request.responseText &&
                    request.responseText.indexOf('ERROR') === 0) {
                    errorCall.call(
                        this,
                        request.responseText,
                        localize('Service:') + ' ' + localize(serviceName)
                    );
                    return;
                }
                if (serviceName === 'login') {
                    myself.api = myself.parseAPI(request.responseText);
                }
                if (serviceName === 'getRawProject') {
                    responseList = request.responseText;
                } else {
                    responseList = myself.parseResponse(
                        request.responseText
                    );
                }
                callBack.call(null, responseList, service.url);
            }
        };
        request.send(this.encodeDict(postDict));
    } catch (err) {
        errorCall.call(this, err.toString(), service.url);
    }
};
