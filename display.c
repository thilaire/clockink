
/* display the hour "hh:mm"
hour is a 16-bit BCD word with hour and min */
void displayHour(uint16_t hour){
	/* keep the digits displayed */
	static uint16_t old_hour = 0xFFFF;
	
	/* horizontal and vertical positions of the digits */
	const int posx[4] = {488, 418, 312, 240};
	const int posy = 96;
	
	display.setPartialWindow(240, 96, 320, 336);
	display.firstPage();
	do{
		/* display each digit if it has not changed */
		uint16_t h = hour, oh = old_hour;
		int* px = &posx;
		for(int i=0; i<4; i++){
			if (h&15 != oh&15)
			display.drawImage(digit_Large_allArray[h&15], px++, posy, 72, 116);
			h >>=4;
			oh >>= 4;
		}
	} while (display.nextPage());

	/* keep the displayed hour */
	old_hour = hour;
}

/* display the date */
void displayDate(const t_date* date){

}