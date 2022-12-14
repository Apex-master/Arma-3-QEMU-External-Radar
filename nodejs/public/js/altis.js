Arma3Map.Maps.altis = {
    CRS: MGRS_CRS(0.006839, 0.006836, 212),
    tilePattern: '/maps/altis/{z}/{x}/{y}.png',
    maxZoom: 6,
    minZoom: 0,
    defaultZoom: 3,
    attribution: '&copy; Bohemia Interactive',
    tileSize: 212,
    center: [15000,15000],
	worldSize: 30720,
	title: 'Altis',
	preview: 'https://arma3.com/assets/img/screenshots/large/arma3_screenshot_38.jpg',
	cities: [
		{name:"Therisa",x:10618.9,y:12237.3},
		{name:"Zaros",x:9091.81,y:11961.9},
		{name:"Poliakko",x:10966.5,y:13435.3},
		{name:"Katalaki",x:11701.1,y:13672.1},
		{name:"Alikampos",x:11112.6,y:14573.7},
		{name:"Neochori",x:12502,y:14337},
		{name:"Stavros",x:12950.1,y:15041.6},
		{name:"Lakka",x:12282,y:15732.3},
		{name:"Agios Dionysios",x:9187.95,y:15947.8},
		{name:"Panochori",x:5033.31,y:11245.2},
		{name:"Topolia",x:7375.81,y:15429.5},
		{name:"Ekali",x:17059.7,y:9992.32},
		{name:"Pyrgos",x:16780.6,y:12604.5},
		{name:"Orino",x:10410.4,y:17243.1},
		{name:"Neri",x:4116.11,y:11736.1},
		{name:"Kore",x:7062.42,y:16472.1},
		{name:"Kavala",x:3458.95,y:12966.4},
		{name:"Aggelochori",x:3687.78,y:13776.1},
		{name:"Koroni",x:11786.7,y:18372.4},
		{name:"Gravia",x:14479.8,y:17614.3},
		{name:"Anthrakia",x:16584.3,y:16104},
		{name:"Syrta",x:8625.13,y:18301.6},
		{name:"Negades",x:4885.98,y:16171.3},
		{name:"Galati",x:10270.3,y:19036},
		{name:"Telos",x:16207,y:17296.7},
		{name:"Charkia",x:18049.1,y:15264.1},
		{name:"Athira",x:13993,y:18709.4},
		{name:"Dorida",x:19336.9,y:13252.3},
		{name:"Ifestiona",x:12787,y:19679.3},
		{name:"Chalkeia",x:20194.6,y:11660.7},
		{name:"Agios Konstantinos",x:3948.77,y:17277.8},
		{name:"Abdera",x:9425.42,y:20284},
		{name:"Panagia",x:20490.2,y:8907.12},
		{name:"Nifi",x:19473.3,y:15453.7},
		{name:"Rodopoli",x:18753.4,y:16597.1},
		{name:"Kalithea",x:17826.5,y:18129.4},
		{name:"Selakano",x:20769.8,y:6736.46},
		{name:"Frini",x:14612.5,y:20786.7},
		{name:"Agios Petros",x:19339.4,y:17641.6},
		{name:"Feres",x:21640.7,y:7583.93},
		{name:"Agia Triada",x:16668.5,y:20487},
		{name:"Paros",x:20885.4,y:16958.8},
		{name:"Kalochori",x:21351.6,y:16361.9},
		{name:"Oreokastro",x:4560.45,y:21460.6},
		{name:"Ioannina",x:23199.7,y:19986.6},
		{name:"Delfinaki",x:23908.6,y:20144.7},
		{name:"Sofia",x:25680.5,y:21365.1},
		{name:"Molos",x:26943.9,y:23170.7}
	]
};


// Force zIndex of Leaflet
(function(global){
	var MarkerMixin = {
	  _updateZIndex: function (offset) {
		this._icon.style.zIndex = this.options.forceZIndex ? (this.options.forceZIndex + (this.options.zIndexOffset || 0)) : (this._zIndex + offset);
	  },
	  setForceZIndex: function(forceZIndex) {
		this.options.forceZIndex = forceZIndex ? forceZIndex : null;
	  }
	};
	if (global) global.include(MarkerMixin);
  })(L.Marker);