/**
 * @author lafont_g
 */

function img_preloader() {
    var i = 0;
    imgLoad = new Image();
    
    paths = new Array();
    paths[0] = "img/test1.jpg";
    paths[1] = "img/test2.jpg";
    paths[2] = "img/test3.jpg";
    paths[3] = "img/test4.jpg";

    /* Preloading images */
    for (i = 0; i <= paths.length; ++i)
    {
	imgLoad.src = paths[i];
    }
}