document.querySelector('.animation').addEventListener('click',function(){
	document.querySelector('.animation').classList.add('started');
	document.querySelector('body').className = "canScroll";
	document.querySelector('html').className = "canScroll";
})

for(var i = 0; i < document.getElementById('Character').getElementsByTagName('button').length; i++){
	document.getElementById('Character').getElementsByTagName('button')[i].addEventListener('click',function(){
		document.getElementById('Character').querySelector('.selected').classList.toggle('selected');
		event.target.classList.add('selected');
	})
}

window.addEventListener('load', function(){
	window.scroll(0,0);
	/* $B%?%$%H%k%"%K%a!<%7%g%s=hM}(B */
	var title_logo = document.querySelector('#title_menu h1');
	title_logo.className="loaded " + title_logo.className;
})

