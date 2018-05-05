// gui.js

IDE_Morph.prototype.originalinit = IDE_Morph.prototype.init;
IDE_Morph.prototype.init = function (isAutoFill) {
    IDE_Morph.prototype.originalinit(isAutoFill);
    this.logoURL = this.resourceURL('manykit/manykit.png');
}

IDE_Morph.prototype.originalSetLanguage = IDE_Morph.prototype.setLanguage;
IDE_Morph.prototype.setLanguage = function (lang, callback) {
    var myself = this;

    myself.originalSetLanguage(lang, function () {
        myself.setLanguagePXFrame(lang, callback);
    });
};

IDE_Morph.prototype.setLanguagePXFrame = function (lang, callback) {
    // Load language script for s4a related functions
    var pxframeTranslation = document.getElementById('language'),
        s4aSrc = 'manykit/lang-' + lang + '.js',
        myself = this;
    if (pxframeTranslation) {
        document.head.removeChild(pxframeTranslation);
    }
    if (lang === 'en') {
        return this.reflectLanguage('en', callback);
    }
    pxframeTranslation = document.createElement('script');
    pxframeTranslation.id = 'language';
    pxframeTranslation.onload = function () {
        myself.reflectLanguage(lang, callback);
    };
    document.head.appendChild(pxframeTranslation);
    pxframeTranslation.src = s4aSrc;
};

IDE_Morph.prototype.originalNewProject = IDE_Morph.prototype.newProject
IDE_Morph.prototype.newProject = function () {
    // Disconnect each sprite before creating the new project
    var sprites = this.sprites.asArray()
    sprites.forEach(function (sprite) {
        if (sprite.pxframe) {
            sprite.pxframe.disconnect(true);
        }
    });
    this.originalNewProject();
};
