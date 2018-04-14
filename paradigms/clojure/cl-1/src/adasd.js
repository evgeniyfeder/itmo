function transformOverlay(e, a) {
    var t = e.innerWidth(), s = e.innerHeight(), n = $(".b_contentWrap").height(), i = $("body").width(),
        r = i / 6.4 / 100, o = n / 6.36 / 100;
    a && (r = Math.min(r, o), o = r);
    var l = Math.round((i - t) / 2), c = Math.round((n - s) / 2);
    e.css({
        "-webkit-transform": "translate(" + l + "px, " + c + "px) scale3d(" + r + ", " + o + ", 1)",
        transform: " translate(" + l + "px, " + c + "px) scale3d(" + r + ", " + o + ", 1)"
    })
}
$("#gameeMobile").remove(), Pace.on("done", function () {
    $(".in-app-preloader").hide()
}), foo = function () {
}, foo.prototype.showOverlay = function (e) {
    $(".js-overlay").hide(), $(e).show(), $(".gameFrame").blur(), $(".js-overlayWrap").fadeIn(), $(window).focus()
}, foo.prototype.hideOverlay = function () {
    $(".js-overlayWrap").fadeOut(), $(".gameFrame").focus()
};
var timer = function () {
    this.t = null
};
timer.prototype.start = function () {
    this.t = setInterval(function () {
        ++window.gameeUI.playTime
    }, 1e3)
}, timer.prototype.pause = function () {
    console.log("Pause timer"), clearTimeout(this.t)
}, timer.prototype.resume = function () {
    this.t = setInterval(function () {
        ++window.gameeUI.playTime
    }, 1e3)
}, timer.prototype.stop = function () {
    clearTimeout(this.t), window.gameeUI.playTime = 0
};
var gameeUI = function () {
    this.currentState = "init", this.playTime = 0, this.score = 0, this.highScore = $(".js-highscore").length ? parseInt($(".js-highscore").html().replace(/\s+/g, "")) : 0, this.gameeVer = 1, this.foo = new foo, this.timer = new timer, this.playDisabled = !0
}, GameeBridge = {
    resume: function () {
        isGamee2() ? gameeUI.game2.resume() : window.gameeUI.game.resume()
    }, start: function () {
        isGamee2() ? gameeUI.game2.start(!1) : ""
    }, pause: function () {
        isGamee2() ? gameeUI.game2.pause() : window.gameeUI.game.pause()
    }, restart: function () {
        isGamee2() ? gameeUI.game2.start(!1) : window.gameeUI.game.restart()
    }
};
gameeUI.prototype.init = function (e, a) {
    console.log("GameeJS 2: init"), this.gameeVer = 2, a(e)
}, gameeUI.prototype.gameReady = function () {
    console.log("GameeJS 2: ready"), this.setGameReady()
}, gameeUI.prototype.requestSocial = function () {
    console.log("GameeJS 2: Socials requested")
}, gameeUI.prototype.saveState = function () {
    console.log("GameeJS 2: save state")
}, gameeUI.prototype.setController = function () {
    this.setGameReady()
}, gameeUI.prototype.gameTwLink = function (e) {
    return "https://twitter.com/share?text=Attention%20please,%20I%20have%20just%20scored%20" + e + "%20in%20" + gameGlobals.game_name + "!%20%40gameeapp%20&url=" + gameGlobals.game_url
}, gameeUI.prototype.gameLoaded = function () {
    this.game = gameeGame($(".gameFrame")[0]), gameeUI.game2 = gamee2Game($(".gameFrame")[0], gameeUI)
}, gameeUI.prototype.updateScore = function (e) {
    var a = parseInt(e), t = e / (this.highScore / 100) + "%";
    window.gameeUI.score = e, $(".js-score").html(a), $(".js-scoreUnderlay").height(t)
}, gameeUI.prototype.gameStart = function () {
    this.currentState = "playing", this.timer.start(), this.updateScore(0), isGamee2() && GameeBridge.start(!1)
}, gameeUI.prototype.gameOver = function () {
    var e = parseInt($(".js-score").html());
    this.currentState = "gameOver", $(".share-tw").attr("href", this.gameTwLink(e)), $(".this-share").addClass("visible"), this.saveScore(window.gameeUI.score), this.sendMixpanel(window.gameeUI.score), this.timer.stop(), $("#sidebar-ranks .items2").remove(), this.foo.showOverlay(".js-overlayOver")
}, gameeUI.prototype.gameRestart = function () {
    $(".this-share").removeClass("visible"), GameeBridge.restart()
}, gameeUI.prototype.gamePause = function () {
    this.currentState = "paused", this.timer.pause(), this.foo.showOverlay(".js-overlayPaused")
}, gameeUI.prototype.gameResume = function () {
    this.currentState = "playing", this.foo.hideOverlay(), this.timer.resume(), GameeBridge.resume()
}, gameeUI.prototype.pauseGame = function () {
    this.gamePause(), GameeBridge.pause(), this.timer.pause()
}, gameeUI.prototype.setGameReady = function () {
    setTimeout(function () {
        gameeUI.playDisabled = !1, $(".js-overlayWrap").addClass("gameReady")
    }, 400)
}, gameeUI.prototype.sendMixpanel = function (e) {
    mixpanel.track("Game Played", {
        "game name": gameGlobals.game_name,
        "game genre": gameGlobals.game_genre,
        "game score": e,
        "game play time": this.playTime,
        source: gameGlobals.game_source,
        "web version": "desktop"
    })
}, gameeUI.prototype.sendMixpanelShare = function (e, a, t) {
    mixpanel.track("Web Game Shared", {type: e, screen: a, "web version": t})
}, gameeUI.prototype.saveScore = function (e) {
    var a = window.location.pathname, t = (new Date).getTime(), s = $("#dataId").data(),
        n = CryptoJS.AES.encrypt(JSON.stringify({score: e, timestamp: t}), s.id, {format: CryptoJSAesJson}).toString(),
        i = {score: e, url: a, play_time: gameeUI.playTime, hash: n};
    if (isFacebook()) {
        var r = FacebookUserData.getUserData();
        i.app_scoped_user_id = r.app_scoped_user_id, i.user_id = r.user_id
    }
    gameeUI.sendScoreData(i)
}, gameeUI.prototype.sendScoreData = function (e) {
    var a = JSON.stringify(e), t = getBotsApiUrl() + "/set-web-score-qkfnsog26w7173c9pk7whg0iau7zwhdkfd7ft3tn";
    $.ajax({
        type: "POST", url: t, data: a, success: function (e) {
            console.log("Gamee: score saved"), (isTelegram() || isKik() || isFacebook()) && (window.gameeUI.getFullRankings(), window.gameeUI.setGameOverRankings(e), $(".js-overlayOver .rankings").show())
        }, dataType: "json", crossDomain: !0
    })
}, gameeUI.prototype.setStartRankings = function (e) {
    var a = e.result.ranking, t = 0 != Object.keys(a.beforeMe).length ? a.beforeMe : "",
        s = 0 != Object.keys(a.afterMe).length ? a.afterMe : "", n = a.me, i = "", r = "", o = "", l = 1, c = 1;
    window.gameeUI.getFullRankings(), 0 != Object.keys(a.me).length && (n.score || $("#sidebar-ranks .area").append('<div class="items2"><div class="row me"><div class="line"><div class="number">' + (n.rank ? n.rank + "." : "-") + '</div><div class="name">' + n.username + '</div><div class="points">' + (n.score ? n.score : "-") + "</div></div></div></div>"));
    var m = Object.keys(a.beforeMe).length + Object.keys(a.afterMe).length + 1;
    n.rank || (l = 2, c = 0), 1 == n.rank && (l = 0, c = 2), n.rank == m && (l = 2, c = 0), m > 3 && $(".cRankingsBtn").css("display", "block"), $(".startRankings .rankings .items .item").remove();
    var d = 1;
    if (0 != Object.keys(a.beforeMe).length)for (var u in t) {
        if (i += '<div class="item"><div class="pic_wrap"><img src="' + addProfilePicture(t[u].profile_picture) + '" class="pic" /></div><div class="username"><span>' + formatUsername(t[u].username) + '</span></div><div class="points">' + (t[u].score ? t[u].score : "-") + "</div></div>", d === l)break;
        d++
    }
    0 != Object.keys(a.me).length && (o = '<div class="item me"><div class="pic_wrap"><img src="' + addProfilePicture(n.profile_picture) + '" class="pic" /></div><div class="username"><span>Me</span></div><div class="points">' + (n.score ? n.score : "-") + "</div></div>");
    if (0 != Object.keys(a.afterMe).length)for (var u in s)r += '<div class="item"><div class="pic_wrap"><img src="' + addProfilePicture(s[u].profile_picture) + '" class="pic" /></div><div class="username"><span>' + formatUsername(s[u].username) + '</span></div><div class="points">' + (s[u].score ? s[u].score : "-") + "</div></div>";
    $(".startRankings .rankings .items").append(i + o + r), $(".startRankings .rankings").addClass("visible")
}, gameeUI.prototype.setGameOverRankings = function (e) {
    var a = e.result.ranking, t = 0 != Object.keys(a.beforeMe).length ? a.beforeMe : "",
        s = 0 != Object.keys(a.afterMe).length ? a.afterMe : "", n = a.me, i = "", r = "", o = 1, l = 1,
        c = Object.keys(a.beforeMe).length + Object.keys(a.afterMe).length + 1;
    1 == n.rank && (o = 0, l = 2), n.rank == c && (o = 2, l = 0), $(".rankings .items .item").remove();
    var m = 1;
    if (0 != Object.keys(a.beforeMe).length)for (var d in t) {
        if (i += '<div class="item"><div class="pic_wrap"><img src="' + addProfilePicture(t[d].profile_picture) + '" class="pic" /></div><div class="username"><span>' + formatUsername(t[d].username) + '</span></div><div class="points">' + (t[d].score ? t[d].score : "-") + "</div></div>", m === o)break;
        m++
    }
    0 != Object.keys(a.me).length && (meRankTpl = '<div class="item me"><div class="pic_wrap"><img src="' + addProfilePicture(n.profile_picture) + '" class="pic" /></div><div class="username"><span>Me</span></div><div class="points">' + (n.score ? n.score : "-") + "</div></div>");
    if (0 != Object.keys(a.afterMe).length)for (var d in s)r += '<div class="item"><div class="pic_wrap"><img src="' + addProfilePicture(s[d].profile_picture) + '" class="pic" /></div><div class="username"><span>' + formatUsername(s[d].username) + '</span></div><div class="points">' + (s[d].score ? s[d].score : "-") + "</div></div>";
    $(".js-overlayOver .rankings .items").append(i + meRankTpl + r), $(".js-overlayOver .rankings").addClass("visible"), window.dispatchEvent(new Event("resize"))
}, gameeUI.prototype.setFullRankings = function (e) {
    var a = e.result.ranking, t = null === e.result.myRank ? "0" : e.result.myRank, s = e.result.membersCount;
    $(".js-overlayOver .membersCount").html(s), $(".js-overlayOver .myPosition").html(t + nth(t)), $("#sidebar-ranks .items .row").remove();
    for (var n in a) {
        var i = a[n].rank === t ? "me" : "",
            r = '<div class="avatar"><img src="' + addProfilePicture(a[n].profile_picture) + '" class="pic" /></div>';
        $("#sidebar-ranks  .items").append('<div class="row ' + i + '"><div class="line"><div class="number">' + a[n].rank + ".</div>" + r + '<div class="name">' + a[n].username + '</div><div class="points">' + a[n].score + "</div></div></div>")
    }
}, gameeUI.prototype.getFullRankings = function () {
    var e = window.location.pathname, a = {url: escape(e)};
    isFacebook() && (a.facebook_user_id = FacebookUserData.getUserData().app_scoped_user_id);
    var t = getBotsApiUrl() + "/api/game-url-ranking";
    $.ajax({
        type: "GET", url: t, data: a, xhrFields: {withCredentials: !0}, success: function (e) {
            console.log("Game: requested rankings"), window.gameeUI.setFullRankings(e)
        }, beforeSend: function (e) {
            e.setRequestHeader("Authorization", "Basic " + btoa("web-api:1k2tnlowfvzfjursfhf523fuenc1guzwxfq8jgc8"))
        }, error: function (e, a) {
        }, dataType: "json", crossDomain: !0
    })
}, gameeUI.prototype.setFullRankingsPopup = function (e) {
    var a = e.result.ranking, t = null === e.result.myRank ? "0" : e.result.myRank, s = e.result.membersCount;
    if ($("#overlay-standing .membersCount").html(s), $("#overlay-standing .myPosition").html(t + nth(t)), $("#overlay-standing .items .row").remove(), Object.keys(a).length > 0)for (var n in a) {
        var i = a[n].rank === t ? "me" : "", r = "";
        a[n].profile_picture && (r = '<div class="avatar"><img src="' + a[n].profile_picture + '" class="pic" /></div>'), $("#overlay-standing .items").append('<div class="row ' + i + '"><div class="line"><div class="number">' + a[n].rank + ".</div>" + r + '<div class="name">' + a[n].username + '</div><div class="points">' + a[n].score + "</div></div></div>")
    }
}, gameeUI.prototype.getFullRankingsPopup = function () {
    var e = window.location.pathname, a = {url: escape(e)};
    isFacebook() && (a.facebook_user_id = FacebookUserData.getUserData().app_scoped_user_id);
    var t = getBotsApiUrl() + "/api/game-url-ranking";
    $.ajax({
        type: "GET", url: t, data: a, xhrFields: {withCredentials: !0}, success: function (e) {
            console.log("Game: requested rankings"), window.gameeUI.setFullRankingsPopup(e)
        }, beforeSend: function (e) {
            e.setRequestHeader("Authorization", "Basic " + btoa("web-api:1k2tnlowfvzfjursfhf523fuenc1guzwxfq8jgc8"))
        }, error: function (e, a) {
        }, dataType: "json", crossDomain: !0
    })
}, gameeUI.prototype.getStats = function () {
    var e = window.location.pathname, a = {url: escape(e)};
    if (isFacebook()) {
        var t = this;
        FacebookUserData.addAfterLoginCallback(function () {
            a.facebook_user_id = FacebookUserData.getUserData().app_scoped_user_id, FacebookUserData.isLoggedIn() ? t.getSurroundingRankings(a) : ($("#sidebar-ranks .ranks-wrap").hide(), $(".msg-wrap.fb-connect").css("display", "table"))
        })
    } else this.getSurroundingRankings(a)
}, gameeUI.prototype.getSurroundingRankings = function (e) {
    var a = getBotsApiUrl() + "/api/game-url-surrounding-ranking";
    $.ajax({
        type: "GET", url: a, data: e, success: function (e) {
            isEmpty(e.result.ranking) || (window.gameeUI.setStartRankings(e), $(".js-overlayPlay .rankings").show())
        }, xhrFields: {withCredentials: !0}, beforeSend: function (e) {
            e.setRequestHeader("Authorization", "Basic " + btoa("web-api:1k2tnlowfvzfjursfhf523fuenc1guzwxfq8jgc8"))
        }, error: function (e, a) {
        }, crossDomain: !0
    })
}, window.gameeUI = new gameeUI, $(window).on("keypress", function (e) {
    (0 == e.keyCode || 32 == e.keyCode) && ("init" == window.gameeUI.currentState && gameeUI.playDisabled === !1 ? ($(".js-overlayPlay").addClass("this-triggered"), window.gameeUI.foo.hideOverlay(), gameeUI.gameStart(), setTimeout(function () {
        $(".js-overlayPlay").removeClass("this-triggered")
    }, 1e3)) : "playing" == window.gameeUI.currentState || ("paused" == window.gameeUI.currentState ? window.gameeUI.gameResume() : "gameOver" == window.gameeUI.currentState && (window.gameeUI.foo.hideOverlay(), GameeBridge.restart()))), (114 === e.keyCode || 82 === e.keyCode) && "gameOver" == window.gameeUI.currentState && (window.gameeUI.foo.hideOverlay(), GameeBridge.restart())
}), $(".child-pushSpace").on("click", function (e) {
    console.log("Space pressed."), "init" == window.gameeUI.currentState && gameeUI.playDisabled === !1 ? ($(".js-overlayPlay").addClass("this-triggered"), window.gameeUI.foo.hideOverlay(), gameeUI.gameStart(), setTimeout(function () {
        $(".js-overlayPlay").removeClass("this-triggered")
    }, 1e3)) : "playing" == window.gameeUI.currentState || ("paused" == window.gameeUI.currentState ? window.gameeUI.gameResume() : "gameOver" == window.gameeUI.currentState && (window.gameeUI.foo.hideOverlay(), GameeBridge.restart()))
}), $(".js_resume").on("click", function (e) {
    window.gameeUI.gameResume()
});
var overlayEmbed = $(".overlay-embed"), clipboard = new Clipboard(".btn-copy");
clipboard.on("success", function (e) {
    $("#game_url").css("border-color", "#5ac546"), $(".btn-copied").css("display", "block"), $(".btn-copy").css("display", "none"), setTimeout(function () {
        $(".btn-copied").css("display", "none"), $(".btn-copy").css("display", "block")
    }, 4e3), e.clearSelection()
}), $(".btn-embed-game").on("click", function (e) {
    overlayEmbed.addClass("visible"), setTimeout(function () {
        document.getElementById("game_url").select()
    }, 500)
}), $(".close-popup").on("click", function (e) {
    $(this).parents(".overlay").removeClass("visible"), $("#game_url").css("border-color", "#b1c1c3")
}), $(".preloader.main").hide(), $(window).on("load", function () {
    var e = $(".gameFrame");
    window.gameeUI.gameLoaded(), e.attr("src", e.data("src")), (isTelegram() || isKik() || isFacebook()) && window.gameeUI.getStats(), $("html").addClass("this-loaded"), window.innerWidth < 640 && transformOverlay($(".b_contentWrap"), !0), window.addEventListener("resize", function () {
        document.body.offsetWidth < 640 ? transformOverlay($(".b_contentWrap"), !0) : ($(".b_contentWrap").css({
            "-webkit-transform": "none",
            transform: "none"
        }), $("#gameeDesktop #overlay-standing").removeClass("visible"))
    })
}), $(".js_pause").on("click", function () {
    window.gameeUI.pauseGame()
}), $(".js_restart").on("click", function () {
    window.gameeUI.gameRestart()
}), $(".cRankingsBtn").on("click", function (e) {
    e.preventDefault(), $("#gameeDesktop #overlay-standing").addClass("visible"), window.gameeUI.getFullRankingsPopup()
}), $(".cRankingsBtn_close").on("click", function (e) {
    e.preventDefault(), $("#gameeDesktop #overlay-standing").removeClass("visible")
}), $(".this-share a, .js_shareFB, .js_shareTW, .twitter-share-button, .fb-like, .share-telegram").on("click", function (e) {
    share_screen = $(this).data("screen"), share_type = $(this).data("type"), share_version = $(this).data("version"), window.gameeUI.sendMixpanelShare(share_type, share_screen, share_version)
}), $(".on-fb").on("click", function (e) {
    var t = ($("body").attr("data-bot-deep-link-base"), $("body").data("facebook-bot-app-id"));
    FB.ui({method: "send", app_id: t, link: gameGlobals.game_fullUrl})
}), $(document).on("click", ".challenge-btn.on-telegram, .share-telegram", function (e) {
    TelegramGameProxy.shareScore()
}), $(".re-request-friends-permission, .action-fb-connect").on("click", function (e) {
    e.preventDefault(), FacebookUserData.forceRelogin()
});