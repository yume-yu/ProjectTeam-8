document.querySelector('.animation').addEventListener('click',function(){
	document.querySelector('.animation').classList.add('started');
	document.querySelector('body').className = "canScroll";
	document.querySelector('html').className = "canScroll";
})

function switchExp(label){
	document.getElementById(label).classList.toggle('selected');
}

document.getElementById('Character').getElementsByTagName('button')[0].addEventListener('click',function(){
	document.getElementById('Character').getElementsByClassName('selected')[1].classList.toggle('selected');
	event.target.classList.add('selected');
	for(var i = 0; i < document.getElementById('Character').getElementsByTagName('div').length; i++){
		document.getElementById('Character').getElementsByTagName('div')[i].classList.remove('selected');
	}
	switchExp('arist_exp');
})
document.getElementById('Character').getElementsByTagName('button')[1].addEventListener('click',function(){
	document.getElementById('Character').getElementsByClassName('selected')[1].classList.toggle('selected');
	//document.getElementById('Character').querySelector('.selected').classList.toggle('selected');
	event.target.classList.add('selected');
	for(var i = 0; i < document.getElementById('Character').getElementsByTagName('div').length; i++){
		document.getElementById('Character').getElementsByTagName('div')[i].classList.remove('selected');
	}
	switchExp('naoki_exp');
})
document.getElementById('Character').getElementsByTagName('button')[2].addEventListener('click',function(){
	document.getElementById('Character').getElementsByClassName('selected')[1].classList.toggle('selected');
	//document.getElementById('Character').querySelector('.selected').classList.toggle('selected');
	event.target.classList.add('selected');
	for(var i = 0; i < document.getElementById('Character').getElementsByTagName('div').length; i++){
		document.getElementById('Character').getElementsByTagName('div')[i].classList.remove('selected');
	}
	switchExp('lirel_exp');
})

window.addEventListener('load', function(){
	window.scroll(0,0);
	/* $B%?%$%H%k%"%K%a!<%7%g%s=hM}(B */
	var title_logo = document.querySelector('#title_menu h1');
	title_logo.className="loaded " + title_logo.className;
})

