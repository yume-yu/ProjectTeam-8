document.querySelector('.animation').addEventListener('click',function(){
	document.querySelector('.animation').classList.add('started');
	document.querySelector('body').className = "canScroll";
	document.querySelector('html').className = "canScroll";
})

window.addEventListener('load', function(){
	/* $B%?%$%H%k%"%K%a!<%7%g%s=hM}(B */
	var title_logo = document.querySelector('#title_menu h1');
	title_logo.className="loaded " + title_logo.className;
})

