

// pour que les video à la gauche du lecteur change
// le fichier à jouer en plus de marquer le changement
// du vidéo sélectionné
$(document).ready(function() {
   $('li.videoSelection').click(function() {
      var videoPlayer = document.getElementById('localPlayer');
      var theSource = videoPlayer.getElementsByTagName('source');  // retourne un vecteur...
      // l'attribu privé data-video précise le fichier
      theSource[0].src = $(this).attr("data-video");
      videoPlayer.load();
      videoPlayer.play();  // lancer directement
      // marquer qu'un nouveau vidéo joue
      $('.videoSelected').removeClass('videoSelected');
      $(this).addClass('videoSelected');
   });
});

// pour le changement d'une playlist de vidéos
$(document).ready(function() {
   $('li.playlistSelection').click(function() {

      // changement de sélection de la librairie de vidéos à regarder
      $('.playlistSelected').removeClass('playlistSelected');
      // très laid: allez sélectionner la case du table sous l'item de la liste...
      $(this).children().eq(0).children().eq(0).children().eq(0).children().eq(3).addClass('playlistSelected');
      
      var pl = $('#playlistLocation').children();
      var matchingID = $(this).attr("data-playlist");

      // changer la visibilité de la playlist du DOM
      // par celle sélectionnée et masquer les autres
      for (var i=0; i<pl.length; i++) {
         if (matchingID == pl.eq(i).attr("id")) {
            pl.eq(i).css( "display", "block"); 
         }
         else {
            pl.eq(i).css( "display", "none");
         }
      }
  });
});




