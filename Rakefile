# Sergio Campama 2011
# http://kaipi.me
# Tuned by Jose L. Honorato
#
# Made for the TI MSP430 LaunchPad
# http://ti.com/launchpadwiki
#
# Released under the Beerware License
# http://en.wikipedia.org/wiki/Beerware

#Setting the compiler
cc = "msp430-gcc"

#Check if a target mcu was specified
mcu = ENV['mcu']
#If no mcu specified'msp430f5529' will be used
mcu ||= "msp430f5529"


#Setting the FLAGS for compile and link time. If using a different MSP430 be sure to change
#the mmcu option
cflags = "-mmcu=#{mcu} -mcpu=430x -c -fstack-check -O2 -Wall -std=c99 -fpack-struct -fdata-sections -ffunction-sections -g "
#cflags = "-mmcu=#{mcu} -c -Wextra -O2 "
lflags = "-mmcu=#{mcu} -mcpu=430x -Wl,--gc-sections"

commit_version = `git log -1 | grep commit | head -1 | sed 's/commit //' | cut -c 1-8`.strip;
puts "Using commit %s\n" % commit_version
if commit_version != ""
    cflags += "-DCOMMIT_VERSION='\"%s\"' " % commit_version
end

testing = ENV['test']
if testing
    cflags += "-DTESTING "
end

#Defining the folder where the compiled objects will reside
obj_dir = 'obj'
directory obj_dir

#Including all the subfolders inside src to be able to use '#include <path/in/src/header.h>'
includes = FileList['src/**/*.h'].collect {|d| File.dirname(d)}
includes.uniq!
cflags += includes.join(' -I').insert(0, '-I') unless includes.empty?

#Include all source files inside src
#Remember, this is for a single app, so there is no purpose in placing source files of another project
#However, this would be the place to include files from other projects, or libraries outside this project
src_files = FileList['src/**/*.c']
obj_files = src_files.collect { |src| File.join(obj_dir, File.basename(src).ext('obj'))}

#The name of the output binary
bin_out = 'bin.elf'

desc "Just in case someone likes to call it 'build'"
task :build => :link

desc "The default compiles and links"
task :default => :link

desc "Link the compiled objects into the binary"
task :link => :compile do
	puts "Linking binary for #{mcu}..."
	`#{cc} #{lflags} #{obj_files.join(" ")} -o #{bin_out}`
	`msp430-objcopy --output-target=ihex bin.elf bin.ihex`
	#This is to check that the output status was 0, if not, something bad happened
	abort "Abort: Error linking #{bin_out}" unless $?.to_i == 0 
	puts "#{bin_out} and bin.ihex succesfully generated!"
end

desc "Compile all source files"
task :compile => obj_dir do
	`rm -rf #{File.join(obj_dir, '*')}/* #{bin_out}`
	src_files.each do |source|
		puts "Compiling #{File.basename(source)}..."
		`#{cc} #{cflags} #{source} -o #{File.join(obj_dir, File.basename(source).ext('obj'))}`
		#This is to check that the output status was 0, if not, something bad happened
		abort "Abort: Error compiling #{File.basename(source)}" unless $?.to_i == 0
	end
end

desc "Installs the binary into the uC"
task :install do
	abort "Abort: #{bin_out} not found. Run 'rake' first" unless File.exists?(bin_out)
	puts "Installing bin.ihex..."
	#`./goodfet.bsl -c /dev/ttyUSB0 -r -e -I -S 38400 -P int_vec.txt -p bin.ihex`
	`mspdebug rf2500 "prog bin.elf"`
	abort "Abort: Error installing #{bin_out}" unless $?.to_i == 0
	puts "#{bin_out} succesfully installed!"
end

desc "Presents the usage to the user"
task :help do
	puts "Usage: 'rake [mcu=msp430g2211 | install | build | help]'"
	puts "When the mcu parameter is not specified, it will use the 'msp430g2211'\noption, as this is the default one on the msp430 Launchpad"
end
