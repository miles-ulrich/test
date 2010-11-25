#!/usr/bin/perl
#$Id: extract-table.pl,v 24.1 2006/10/21 01:19:37 raman Exp $
# Accepts a URI and table spec
#returns a csv file
use strict;
use FileHandle;
use LWP::UserAgent;
use HTML::TableExtract;
use IO::File;
use Getopt::Long;
use vars qw (%options);
my ($url, $file, $task, $depth, $count, $cols, $position);

my %options = (task => \$task,
           url => \$url,
file => \$file,
           depth => \$depth,
count => \$count,
position => \$position,
headers => \$cols);
GetOptions (\%options,
            'file=s',
            'url=s',
            'task=s',
            'depth=i',
            'count=i',
            'position=s',
            'headers=s');
$task ||= "extract-table";
my $input;
if (defined ($file)) {
  $input = $file;
} else {
  $input="/tmp/$options{task}.html";
  RetrieveURLToFile($url, $input);
}

my $te;
if ( defined ($cols)) {
  my @headers = split(',', $cols);
  $te = new HTML::TableExtract(headers=>\@headers);
} else {
 $te = new HTML::TableExtract( depth => $depth, count=>$count); 
}
$te->parse_file($input);
my $output = new FileHandle (">>  table.csv");
my ($ts,$row);
foreach $ts ($te->table_states) {
          foreach $row ($ts->rows) {
             print ( '"'.$position.'","'.join('","', @$row).'"', "\n");
          }
        }

$output->close();

if (defined ($url)) {
  unlink ($input);
}
# {{{  retrieve URL to file

sub RetrieveURLToFile {
  my ($url, $filename) = @_;
  my $ua = new LWP::UserAgent;
  # Create a request
  my $req = new HTTP::Request( 'GET' => $url);
  # Pass request to the user agent and get a response back
  my $res = $ua->request($req, $filename);
  if ($res->is_success()) {
  } elsif ($res->is_error()) {
    exit ("Retrieval for $url failed\n");
  }
}

# }}}
1;
