<?php

$positions = array(
	"QB",
	"RB",
	"WR",
	"TE",
	"K",
	"DST",
);

$url = "http://www.fantasypros.com/nfl/rankings/weekly-rankings.php?position=";

foreach ($positions as $position) {
  system("./extract-table.pl --url=\"http://www.fantasypros.com/nfl/rankings/weekly-rankings.php?position={$position}\" --position=\"{$position}\" | tail -n+2");
}
