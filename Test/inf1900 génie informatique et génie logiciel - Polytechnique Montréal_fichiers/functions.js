var PhotosCarousel = [
    "/inf1900/preambule/imagesRobot/images/5robots.jpg",
    "/inf1900/preambule/imagesRobot/images/escalier+3robots.jpg",
    "/inf1900/preambule/imagesRobot/images/lt+usb.jpg",
    "/inf1900/preambule/imagesRobot/images/jaune+ligne.jpg",
    "/inf1900/preambule/imagesRobot/images/ligne+3robots.jpg",
    "/inf1900/preambule/imagesRobot/images/oscillo+blanc.jpg",
    "/inf1900/preambule/imagesRobot/images/oscillo+noir.jpg",
    "/inf1900/preambule/imagesRobot/images/ps2+bleu.jpg",
    "/inf1900/preambule/imagesRobot/images/3robots.jpg",
    "/inf1900/preambule/imagesRobot/images/eviterPoteaux.jpg",
    "/inf1900/preambule/imagesRobot/images/combatants.jpg",
    "/inf1900/preambule/imagesRobot/images/arriere.jpg",
    "/inf1900/preambule/imagesRobot/images/optimus.jpg",
    "/inf1900/preambule/imagesRobot/images/carteMere.jpg"
];


if (!String.prototype.trim) {
    String.prototype.trim = function () {
        return this.replace(/^\s+|\s+$/g, '');
    };
}







$(document).ready(function(){

    //FOnctionnalite des liens rapides
    $(".quicklinks select").change(function(){
        var link = $(".quicklinks select").val();
        if (link != -1)
            window.location.href = link;
    });


    //pour faire la recherche lorsqu'on presse ENTER
    $('.searchbox input.searchquery').bind('keypress', function(e) {
        var code = e.keyCode || e.which;
        if(code == 13) {
            $(".searchbox .btn.search").trigger('click');
        }
    });


    $(".main-menu .navbar li.dropdown").mouseleave(function(){
        $(this).removeClass('open');
    });

    $(".main-menu .navbar li.dropdown").mouseenter(function(){
        $(this).addClass('open');
    });

    $(".searchbox .btn.search").click(function(){
        var searchEngine = $('input[name=search-engine]:checked', '.searchbox').val();

        query = "as_q=" + $(".searchbox input.searchquery").val();

        if (searchEngine != "http://www.google.com"){
            query +=  "&sitesearch=" + searchEngine;
        }

        window.open("http://www.google.com/search?" + query);
    });


    /*$("#popupPhotos a.download-image").click(function(e){

        e.preventDefault();
       var imageLink = $(this).parent().parent().find("img:first").attr("src");
        window.open(imageLink);
    });*/


    function removeIndexDotPHP(url){
        if (url.slice(-9) == "index.php"){
            return url.substring(url,url.length - 9);
        }

        // juste au cas ou...
        if (url.slice(-1) != "/"){
            url += "/";
        }

        return url;
    }

    function capitaliseFirstLetter(string)
    {
        string = string.trim();
        string = string.toLowerCase();

        return string.charAt(0).toUpperCase() + string.slice(1);
    }


    var SelectActiveMenuItem = (function(){
        var currentUrl = location.pathname;
        currentUrl = removeIndexDotPHP(currentUrl);


        $(".main-menu .navbar-inner a").each(function(){
            var $menuItem = $(this);
            var itemUrl = removeIndexDotPHP($(this).attr("href"));

            if (itemUrl == currentUrl){

                $parentElement = $(this).parent();

                while(!($parentElement.prop("tagName") == "UL" && $parentElement.hasClass("nav"))){
                    if ($parentElement.prop("tagName") == "LI"){
                        $parentElement.addClass("active");
                    }

                    $parentElement = $parentElement.parent();
                }



                $menuItem.parent().addClass("active");
            }
        });


        $("a.skinfooteritem").each(function(){
            var $menuItem = $(this);
            var itemUrl = removeIndexDotPHP($(this).attr("href"));

            if (itemUrl == currentUrl){

                $menuItem.addClass("active");
            }
        });



    }());



    var BreadCrumb = (function(){
        var currentUrl = location.pathname;
        currentUrl = removeIndexDotPHP(currentUrl);

        //tous les cas possibles de la homepage
        if (currentUrl != "/inf1900/" && currentUrl != "/inf1900/index.php/" && currentUrl != "/index.php/" && currentUrl != "/"){

            //si la page a ete trouve pour ne pas verifier dans le menu du footer
            var found = false;

            //On cherche dans le menu principal
            $(".main-menu .navbar-inner a").each(function(){
                var $menuItem = $(this);
                var itemUrl = removeIndexDotPHP($(this).attr("href"));

                if (itemUrl == currentUrl){
                    found = true;

                    if ($menuItem.parent().parent().prop("tagName") == "UL" && $menuItem.parent().parent().hasClass("nav")){
                        $("#mainBreadCrumb").prepend("<li class=\"active\">"+capitaliseFirstLetter($menuItem.text())+"</li>");
                    }else{
                        $("#mainBreadCrumb").prepend("<li class=\"active\">"+$menuItem.text()+"</li>");
                    }


                    $parentElement = $(this).parent().parent();

                    while(!($parentElement.prop("tagName") == "UL" && $parentElement.hasClass("nav"))){
                        if ($parentElement.prop("tagName") == "LI"){

                            link = $parentElement.find(">a");

                            if ($parentElement.parent().prop("tagName") == "UL" && $parentElement.parent().hasClass("nav")){
                                $("#mainBreadCrumb").prepend("<li><a href=\""+link.attr("href")+"\">"+capitaliseFirstLetter(link.text())+"</a><span class=\"divider\">/</span></li>");
                            }else{
                                $("#mainBreadCrumb").prepend("<li><a href=\""+link.attr("href")+"\">"+link.text()+"</a><span class=\"divider\">/</span></li>");
                            }

                        }

                        $parentElement = $parentElement.parent();
                    }

                    $("#mainBreadCrumb").prepend("<li><a href=\"/inf1900\">Accueil</a><span class=\"divider\">/</span></li>");

                    $("#mainBreadCrumb").css("display","block");

                    return false;
                }
            });

            if (!found){
                $("a.skinfooteritem").each(function(){
                    var $menuItem = $(this);
                    var itemUrl = removeIndexDotPHP($(this).attr("href"));

                    if (itemUrl == currentUrl){

                        $("#mainBreadCrumb").prepend("<li class=\"active\">"+$menuItem.text()+"</li>");
                        $("#mainBreadCrumb").prepend("<li><a href=\"/inf1900\">Accueil</a><span class=\"divider\">/</span></li>");
                        $("#mainBreadCrumb").css("display","block");

                        return false; //break
                    }
                });
            }

        }
    }());






});


