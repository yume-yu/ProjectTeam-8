function moveLogo(elem){
}

document.getElementById("enter_button").addEventListener('click',function(){
	var elm = document.getElementsByClassName("animation");
	anime({
		targets: elm,
		duration: 2000,
		opacity: 0,
		height: 0,
		complate:function(anim){
			document.querySelector('#title_menu').style.zIndex="1";
			document.querySelector("#title_menu").style.display="none";
		}
	})
	document.querySelector('body').className = "canScroll";
	document.querySelector('html').className = "canScroll";
})

window.addEventListener('load', function(){
	var title_logo = document.querySelector('h1.animation');
	title_logo.className="loaded " + title_logo.className;
})

