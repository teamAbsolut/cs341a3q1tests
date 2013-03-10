desc "Run tests"
task :test do
  puts "Testing"
  Dir.glob('tests/*') do |file|
    fileName = file[/[^\/]*$/]
    solution = File.open( File.join('solutions', fileName ) ).read
    output = `./a3 <#{file}`

    if solution == output
      puts "Passed #{fileName}"
    else
      puts "Failed #{fileName}"
      puts "  Output: #{output}"
    end
  end
end

desc "Run a specific test"
task :specific, :arg1 do |t,args|
  solution = File.open( File.join('solutions', args[:arg1] ) ).read
  output = `./a3 <#{File.join('tests', args[:arg1] ) }`
  if solution == output
    puts "Passed #{args[:arg1]}"
  else
    puts "Failed #{args[:arg1]}"
    puts "  Output: #{output}"
  end
end

desc "Compiles program"
task :compile do
  puts "Compiling"
  `g++ -o a3 a3.cpp`
end

desc "Compiles a debug version"
task :compiledebug do
  puts "Compiling debug version"
  `g++ -o a3 a3.cpp -DDEBUG`
end

task :default => :test
