document.getElementsByTagName('body')[0].classList.toggle('canScroll');
document.getElementsByTagName('html')[0].classList.toggle('canScroll');

function switchExp(label){
	document.getElementById('worldOutlook').getElementsByTagName('div')[label].classList.toggle('selected');
}

document.getElementById('worldOutlook').getElementsByTagName('button')[0].addEventListener('click',function(){
	document.getElementById('worldOutlook').getElementsByClassName('selected')[1].classList.toggle('selected');
	document.getElementById('worldOutlook').getElementsByTagName('button')[0].classList.add('selected');
	for(var i = 0; i < document.getElementById('worldOutlook').getElementsByTagName('div').length; i++){
		document.getElementById('worldOutlook').getElementsByTagName('div')[i].classList.remove('selected');
	}
	switchExp('1');
})
document.getElementById('worldOutlook').getElementsByTagName('button')[1].addEventListener('click',function(){
	document.getElementById('worldOutlook').getElementsByClassName('selected')[1].classList.toggle('selected');
	//document.getElementById('worldOutlook').querySelector('.selected').classList.toggle('selected');
	document.getElementById('worldOutlook').getElementsByTagName('button')[1].classList.add('selected');
	for(var i = 0; i < document.getElementById('worldOutlook').getElementsByTagName('div').length; i++){
		document.getElementById('worldOutlook').getElementsByTagName('div')[i].classList.remove('selected');
	}
	switchExp('2');
})
document.getElementById('worldOutlook').getElementsByTagName('button')[2].addEventListener('click',function(){
	document.getElementById('worldOutlook').getElementsByClassName('selected')[1].classList.toggle('selected');
	//document.getElementById('worldOutlook').querySelector('.selected').classList.toggle('selected');
	document.getElementById('worldOutlook').getElementsByTagName('button')[2].classList.add('selected');
	for(var i = 0; i < document.getElementById('worldOutlook').getElementsByTagName('div').length; i++){
		document.getElementById('worldOutlook').getElementsByTagName('div')[i].classList.remove('selected');
	}
	switchExp('3');
})
document.getElementById('worldOutlook').getElementsByTagName('button')[3].addEventListener('click',function(){
	document.getElementById('worldOutlook').getElementsByClassName('selected')[1].classList.toggle('selected');
	//document.getElementById('worldOutlook').querySelector('.selected').classList.toggle('selected');
	document.getElementById('worldOutlook').getElementsByTagName('button')[3].classList.add('selected');
	for(var i = 0; i < document.getElementById('worldOutlook').getElementsByTagName('div').length; i++){
		document.getElementById('worldOutlook').getElementsByTagName('div')[i].classList.remove('selected');
	}
	switchExp('4');
})
document.getElementById('worldOutlook').getElementsByTagName('button')[4].addEventListener('click',function(){
	document.getElementById('worldOutlook').getElementsByClassName('selected')[1].classList.toggle('selected');
	//document.getElementById('worldOutlook').querySelector('.selected').classList.toggle('selected');
	document.getElementById('worldOutlook').getElementsByTagName('button')[4].classList.add('selected');
	for(var i = 0; i < document.getElementById('worldOutlook').getElementsByTagName('div').length; i++){
		document.getElementById('worldOutlook').getElementsByTagName('div')[i].classList.remove('selected');
	}
	switchExp('5');
})
document.getElementById('worldOutlook').getElementsByTagName('button')[5].addEventListener('click',function(){
	document.getElementById('worldOutlook').getElementsByClassName('selected')[1].classList.toggle('selected');
	//document.getElementById('worldOutlook').querySelector('.selected').classList.toggle('selected');
	document.getElementById('worldOutlook').getElementsByTagName('button')[5].classList.add('selected');
	for(var i = 0; i < document.getElementById('worldOutlook').getElementsByTagName('div').length; i++){
		document.getElementById('worldOutlook').getElementsByTagName('div')[i].classList.remove('selected');
	}
	switchExp('6');
})

document.getElementById('worldOutlook').getElementsByTagName('button')[6].addEventListener('click',function(){
	document.getElementById('worldOutlook').getElementsByClassName('selected')[1].classList.toggle('selected');
	//document.getElementById('worldOutlook').querySelector('.selected').classList.toggle('selected');
	document.getElementById('worldOutlook').getElementsByTagName('button')[6].classList.add('selected');
	for(var i = 0; i < document.getElementById('worldOutlook').getElementsByTagName('div').length; i++){
		document.getElementById('worldOutlook').getElementsByTagName('div')[i].classList.remove('selected');
	}
	switchExp('7');
})

