#!/usr/bin/perl

# Comments
# This is a one line comment

=This is a
multiline
comment
=cut

# Operators:
# Equal (assignment)    : =
# Addition              : + (+=)
# Subtraction           : - (-=)
# Multiplication        : * (*=)
# Division              : / (/=)
# Modulus               : % (%=)
# Exponent              : ** (**=)
# Add (subtract) one    : ++ (--)
# Bitwise AND           : & (&=)
# Bitwise OR            : | (|=)
# Bitwise XOR           : ^ (^=)
# Bitwise shifts        : << (<<=) and >> (>>=)
# Bitwise NOT           : ~
# Concatenation         : . (.=)
# String multiplication : x
# Range                 : ..
# Variable from object  : ->

# Number comparators:
# Equal              : ==
# Not equal          : !=
# compareTo (java)   : <=>
# Less (or equal)    : < (<=)
# Greater (or equal) : > (>=)

# String comparators:
# Equal              : eq
# Not equal          : ne
# compareTo (java)   : cmp
# Less (or equal)    : lt (le)
# Greater (or equal) : gt (ge)

# Logical operators:
# AND                : and
# Bitwise AND        : &&
# OR                 : or
# Bitwise OR         : ||
# NOT                : not

# Available conditionals:
# IF statement      :   if (...) {...} elsif (...) {...} else {...}
# UNLESS statement  :   unless (...) {...} elsif (...) {...} else {...}
# SWITCH statement  :   switch (...) ???????
# TERNARY           :   (...)? ... : ...

# Available loops:
# WHILE loop        :   while (...) {...}
# UNTILL loop       :   untill (...) {...}
# FOR loop          :   for (...;...;...) {...}
# FOREACH loop      :   foreach VAR (LIST) {...}
# DO WHILE loop     :   do {...} while (...);

# Loop control statements:
# next   : works like C++ continue
# last   : works like C++ break

# Function definition:
# sub NAME {... return ...}
# Args vector can be found at an array named \@_
# Lambdas can be created defining a function without name

# Variables scope:
# Stored just in this block environment             : my
# Stored in this block and sub blocks environments  : local
# Keep it's value through muliple function calls    : state (requires "use feature 'state'" at the top of the code)


# Printing string text
print "========================= Printing =========================\n\n";
$a = 10;
print 'Hello, world $a \n';     # Non-interpolated string
print "Hello, world $a \n";     # Interpolated string
print "\$result\n";

# Prints interpolated text until EOF
$var = <<"EOF";
This is case of double quote so variable value will be
interpolated. For example value of a = $a
EOF
print "$var\n";

# Prints non-interpolated text until EOF
$var = <<'EOF';
This is case of single quote so variable value will not be
interpolated. For example value of a = $a
EOF
print "$var\n";

print "Pure hexadecimal : \x41\n";                         # Prints hexadecimal number
print "Pure octal : \064\n";                               # Prints octal number
print "Character? : \c! \c#\n";                            # ??????
print "Case test : \ujoao, \lJOAO, \Ujoao\E, \LJOAO\E\n";  # Change characters case
print "Backslash test : \Q!?&*#\E\n";                      # Backslash non-alphanumeric characters
print "ASCII string : ".v77.97.114.116.105.110.9786.10.10; # String composed of characters from their code

# These are scalars
print "========================= Scalars ==========================\n\n";
$i = 1234;                         # Positive
$n = -100;                         # Negative
$f = 20.00;                        # Float
$c = 3.14E10;                      # Cientific
$h = 0xffff;                       # Hexadecimal (note the "0x")
$o = 0577;                         # Octal (note the leading zero)
$str = "\unumbers :";              # Strings
print "$str $i $n $f $c $h $o\n\n";

# These are arrays
print "========================== Arrays ==========================\n\n";
@i = (123, 567, 890);                                    # Makes an array
@copy = @i;                                              # Copies the array
$size = @i;                                              # Gives the size of the array
@str = ("Array", ":");                                   # Split opperator
print "$str[0] $str[1] ($i[0], $i[1], $i[-1])\n";        # Arrays are circular at negative index
print "Which number does \$i contains? $i or $i[1]?\n";  # Perl separates scalar, array and hash
@i[0] = 10;
print "Copy : @copy / @i, and size : $size\n";
@seq = (1..10, a..d);                                    # A sequential array
print "Sequential : @seq\n";
$i[10] = 6;                                              # Makes the array bigger
print "Long array size : ", scalar @i, "\n";             # Cast :P
print "Long array max index : ", $#i, "\n\n";            # Gets the length - 1

# These are hashes
print "========================== Hashes ==========================\n\n";
%h = ("key1", "val1", "key2", 2, 3, 90);         # Makes a hash (Note that numbers and strings are mixed)
%h2 = ("key1" => "val1", "key2" => 2, 3 => 90);
%h3 = (key1 => "val1", key2 => 2, 3 => 90);      # This way keys cannot contain space
%copy = %h;                                      # Copies a hash
$size = %h;                                      # Gets the size of a hash
print "\$h{'key1'} = $h{'key1'}\n";
print "\$h{'key2'} = $h{'key2'}\n";
print "\$h{3} = $h{3}\n";
print "Value for 'key1' at copy : $copy{'key1'}\n";
print "Size : $size\n\n";

# Print things about this file
print "====================== About this file =====================\n\n";
print "File name : " . __FILE__ . "\n";
print "Line number : " . __LINE__ . "\n";
print "Package : " . __PACKAGE__ . "\n";
print "These cannot be interpolated __FILE__, __LINE__, __PACKAGE__\n\n";

# References
print "======================== References ========================\n\n";
$scal = 10;
@arr = (10, 20 ,30);
%hash = (Bob => 5, Anne => 10, Paul => 20);
$ref = \$scal;                                         # Gets reference to scalar
print "Got a ", ref($ref), " : $$ref\n";               # Dereferenciating
$ref = \@arr;                                          # Gets reference to array
print "Got an ", ref($ref), " : @$ref\n";              # Dereferenciating
$ref = \%hash;                                         # Gets reference to hash
@keys = keys %$ref;                                    # Dereferenciating
@values = values %$ref;
print "Got a ", ref($ref), " : @keys @values\n";       # ref gives the reference type (SCALAR, ARRAY, HASH)
$ref = [[1,2,3], [4.5], [6], [8, 9, 10]];              # Create anonimous array (square brackets)
print "Got another array : ", $$ref[3][0], "\n";
$ref = {Natty => 10, Carol => 15, Allan => 7};         # Create anonimous hash (curly brackets)
@keys = keys %$ref;
@values = values %$ref;
print "Got another hash : @keys @values\n";
sub PrintHash{
   my (%hash) = @_;
   foreach $item (%hash){
      print "Item : $item\n";
   }
}
$ref = \&PrintHash;                                    # Creates reference to a function
&$ref(%hash);                                          # Calls the reference
print "\n";

# Appending and shifting an array
print "==================== Array opperations =====================\n\n";
@arr = (1, 2, 3);
print "Initial : @arr\n";
push @arr, (4, 5, 6);
print "After push : @arr\n";
pop @arr;
print "After pop : @arr\n";
shift @arr;
print "After shift : @arr\n";
unshift @arr, (-1, 0);
print "After unshift : @arr\n";

# Slicing works as python
@slice = @arr[1..3, 5];
print "Slice : @slice\n";

# Splicing works as Javascript
@nums = 1..20;
print "Before splice : @nums\n";
@splice = splice @nums, 5, 5, 21..25;   # splice @ARRAY, OFFSET [, LENGTH [, LIST]]
print "After splice : @nums\n";
print "Splice : @splice\n";

# Split works as python
@split1 = qw/Rain Drops On Roses And
             Whiskers On Kittens/;                          # Split by whitespace
$strings = "Rain-Drops-On-Roses-And-Whiskers-On-Kittens";
@split2 = split "-", $strings;                              # Split by character
print "First split : @split1\n";
print "Second split : @split2\n";

# Sorting
@sorted = sort @nums;         # Sorts by ASCII number
print "Sorted : @sorted\n";

# Special variable $[ (the first index of all arrays)
@foods = qw(pizza steak chicken burgers);
print "First food with \$[ = 0 : $foods[0]\n";
$[ = 1;
print "First food with \$[ = 1 : $foods[1]\n";
$[ = 0;

# Combining arrays
@odd = (1,3,5);
@even = (2, 4, 6);
@numbers = (@odd, @even);
print "Combined array : @numbers\n\n";

# Slicing a hash
print "===================== Hash opperations =====================\n\n";
%hash = (JohnPaul => 45, Lisa => 30, Kumar => 40);
@array = @hash{JohnPaul, Lisa};
print "Slice from hash values : @array\n";

# Getting keys and values
@keys = keys %hash;
@values = values %hash;
print "Keys : @keys\n";
print "Values : @values\n";

# Checking existence
print "Does Lisa exists? ", exists $hash{Lisa}, "\n";

# Adding and removing elements
$hash{Ali} = 55;
print "Ali added to the hash : $hash{Ali}\n";
delete $hash{Ali};
print "Ali is not among us anymore : ", exists $hash{Ali}, "\n\n";

# Local time
print "=================== Getting current time ===================\n\n";
($sec,$min,$hour,$mday,$mon,$year,$wday,$yday,$isdst) = localtime(); # Gets local time
print "$hour:$min:$sec from $mon $mday, $year, $wday\n";
$date_as_string = localtime();
print "$date_as_string\n";
printf "%02d:%02d:%02d\n\n", $hour, $min, $sec;                          # Formatting
# Use gmtime() for GMT date and time and time() to get epoch time (seconds since 1/1/1970)
# strftime() can format data, a table can be found in https://www.tutorialspoint.com/perl/perl_date_time.htm

# Formats
print "========================= Formats ==========================\n\n";
# This creates the format, and can contain
# @<<<< left-justified field
# @>>>> right-justified field
# @|||| centered field
# @####.## numeric field holder
# @* multiline field holder
format EMPLOYEE =
-------------------------------------
@<<<<<<<<<<<<<<<<<<<<<< @<<
$name $age
@#####.##
$salary
-------------------------------------
.
# Page header format (the $% gets the page number, each page has 60 lines by
# default, this can be changed using $= variable)
format EMPLOYEE_TOP =
-------------------------------------
Name                    Age @<<
                            $%
-------------------------------------
.

select(STDOUT);                     # Sets the format output
$~ = EMPLOYEE;                      # Sets the default format
$^ = EMPLOYEE_TOP;                  # Sets the default header

@n = ("Ali", "Raza", "Jaffer");
@a  = (20,30, 40);
@s = (2000.00, 2500.00, 4000.000);

$i = 0;
foreach (@n){
   $name = $_;
   $age = $a[$i];
   $salary = $s[$i++];
   write;                           # Writes the format at the desired output
}
print "\n";

# Objects (called packages)
print "========================= Objects ==========================\n\n";
# Classes can be in different files, but their name must end with .pm
# and can be imported to our script using the keyword "use"
# Following is the implementation of simple Class.
package MyClass;

sub new {
   print "MyClass::new called\n";
   my $type = shift;            # The package/type name
   my $self = {
       _name => shift
   };                           # Hash with object variables
   return bless $self, $type;
}

# Not necessary
sub DESTROY {
   print "MyClass::DESTROY called\n";
}

sub MyMethod {
   print "MyClass::MyMethod called!\n";
}

sub setName {
   my ( $self, $name ) = @_;
   $self->{_name} = $name if defined($name);
   return $self->{_name};
}


# Following is the implemnetation of Inheritance.
package MySubClass;

@ISA = qw( MyClass );   # Inherits from MyClass (Note: THIS IS A LIST OF PARENTS NAMES)

sub new {
   print "MySubClass::new called\n";
   my $type = shift;            # The package/type name
   my $self = MyClass->new;     # Takes the constructor from the parent
   return bless $self, $type;
}

sub DESTROY {
   print "MySubClass::DESTROY called\n";
}

sub MyMethod {
   my $self = shift;
   $self->SUPER::MyMethod();
   print "   MySubClass::MyMethod called!\n";
}

# Here is the main program using above classes.
package main;

print "Invoke MyClass method\n";

$myObject = MyClass->new("Name1");
$myObject->MyMethod();
$name = $myObject->setName("Gotcha");
print "$name\n";

print "Invoke MySubClass method\n";

$myObject2 = MySubClass->new("Name2");
$myObject2->MyMethod();

print "Create a scoped object\n";
{
	my $myObject2 = MyClass->new("Name3");
}
# Destructor is called automatically here

print "Create and undef an object\n";
$myObject3 = MyClass->new("Name4");
undef $myObject3;

print "Fall off the end of the script...\n";
# Remaining destructors are called automatically here

# Executing bash commands
# Just put the command inside back sticks (`...`) and it'll be executed, and it's result
# will be returned
# More on https://www.tutorialspoint.com/perl/perl_process_management.htm

# File handling
# Read https://www.tutorialspoint.com/perl/perl_files.htm
# Open, read, write, create, copy and delete files

# Directory handling
# Read https://www.tutorialspoint.com/perl/perl_directories.htm
# Open dir, list files, create dir, delete dir and change dir

# Error handling
# Read https://www.tutorialspoint.com/perl/perl_error_handling.htm
# warn    :  Prints the argument with an error message
# die     :  Prints the argument with an error message and stops the program
# carp    :  ...
# cluck   :  ...
# croak   :  ...
# confess :  ...

# Lots of regex
# Read https://www.tutorialspoint.com/perl/perl_regular_expressions.htm
# =~          :  Grep opperator
# /.../       :  Double slash (like quotes)
# ?...?       :  Double question marks
# $`          :  Stores everything before the match (back stick)
# $&          :  Stores the match
# $'          :  Stores everything after the match (single quote)
# s/.../.../  :  Substitution operator
# tr/.../.../ :  Translation operator

# Some usefull useless email sending
# Read https://www.tutorialspoint.com/perl/perl_sending_email.htm

# Socket programming
# Read https://www.tutorialspoint.com/perl/perl_socket_programming.htm
# Basically, connecting to other machines or a server

# CGI programming
# Read https://www.tutorialspoint.com/perl/perl_cgi_programming.htm
# Handling web input/output

# Modulling your program
# Read https://www.tutorialspoint.com/perl/perl_packages_modules.htm

# Other function references
# https://www.tutorialspoint.com/perl/perl_function_references.htm
