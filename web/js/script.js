document.querySelector('.animation').addEventListener('click',function(){
	document.querySelector('.animation').classList.add('started');
	document.querySelector('body').className = "canScroll";
	document.querySelector('html').className = "canScroll";
})

window.addEventListener('load', function(){
	window.scroll(0,0);
	/* タイトルアニメーション処理 */
	var title_logo = document.querySelector('#title_menu h1');
	title_logo.className="loaded " + title_logo.className;
})

