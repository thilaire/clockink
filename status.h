typedef strict {
	uint16 hour;	/* BCD hour */
	uint8 weekday;	
	uint8 date;		/* BCD day of the month */
	uint8 month;	/* BCD month */
	uint8 year;		/* BCD year, after 2000 */
} t_date;

typedef strict {
	t_date date;
	// int. pressure
	// int. temp
	// int. co2
}


void getDateHour(const RV3028& rtc, t_date& date)