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

desc "Generate graphs for part 2"
task :generate do
  if Dir.exist?("input")
    puts "You already generated input files, do you want to regenerate (y/n)? "
    if STDIN.gets.chomp == 'y'
      generateFiles()
    end
  else
    Dir.mkdir "input"
    generateFiles()
  end

  # run our program on the input files
  result = Hash.new {|hash, key| hash[key] = [key]}
  [10, 100, 250, 500, 750, 1000, 2000].each do |i|
    puts "Retrieving time to run on input size #{i}"
    result[i] << `/usr/bin/time -p ./a3 <#{File.join('input', i.to_s)} 2>&1`.split("\n").grep(/real/)[0].split(" ")[1]
    result[i] << `/usr/bin/time -p ./bruteforce <#{File.join('input', i.to_s)} 2>&1`.split("\n").grep(/real/)[0].split(" ")[1]
  end
  puts "input\talgo\tbrute"
  result.values.each do |i|
    puts "#{i[0]}\t#{i[1]}\t#{i[2]}"
  end
end

desc "Compiles program"
task :compile do
  puts "Compiling"
  `g++ -o a3 a3.cpp`
  `g++ -o bruteforce bruteforce.cpp`
end

desc "Compiles a debug version"
task :compiledebug do
  puts "Compiling debug version"
  `g++ -o a3 a3.cpp -DDEBUG`
end

task :default => :test

def randomInRange n, m
  (Random.rand * ( m - n ) + n).round
end

def generateTest nRec, nPoi
  minX, maxX, minY, maxY = -10, 10, -10, 10
  totalarea = (maxY - minY) * (maxX - minX)
  usedarea = 0
  percentused = 0.5
  rectangles = []
  points = []
  nRec.times do
    proposedX1, proposedX2, proposedY1, proposedY2 = 0, 0, 0, 0
    while true
      proposedX1 = randomInRange( minX, maxX )
      proposedX2 = randomInRange( minX, maxX )
      proposedY1 = randomInRange( minY, maxY )
      proposedY2 = randomInRange( minY, maxY )
      if proposedX1 == proposedX2 or proposedY1 == proposedY2
        next
      end
      # reorder to smaller larger
      if proposedX1 > proposedX2
        proposedX1, proposedX2 = proposedX2, proposedX1
      end
      if proposedY1 > proposedY2
        proposedY1, proposedY2 = proposedY2, proposedY1
      end
      bad = false
      rectangles.each do |box|
        # check if the box is completely out of range
        if !( proposedX1 > box[1] or proposedX2 < box[0] or proposedY1 > box[3] or proposedY2 < box[2] )
          bad = true
          break
        end
      end
      next if bad == true
      break
    end
    rectangles << [proposedX1, proposedX2, proposedY1, proposedY2]

    # check if we need to expand the area
    usedarea += (proposedY2 - proposedY1 + 1) * (proposedX2 - proposedX1 + 1)
    if usedarea.to_f/totalarea.to_f > percentused
      minX *= 2
      maxX *= 2
      minY *= 2
      maxY *= 2
      totalarea = (maxY - minY) * (maxX - minX)
    end
  end

  nPoi.times do
    proposedX, proposedY = 0, 0
    while true
      proposedX = randomInRange( minX, maxX )
      proposedY = randomInRange( minY, maxY )
      bad = false
      points.each do |poi|
        if proposedX == poi[0] and proposedY == poi[1]
          bad = true
          break
        end
      end
      next if bad == true
      break
    end
    points << [proposedX, proposedY]
  end

  [rectangles,points]
end

def generateFiles
  [10, 100, 250, 500, 750, 1000, 2000].each do |i|
    puts "generating input file of size #{i}"
    filename = File.join("input", i.to_s)
    if File.exist?( filename )
      File.delete( filename )
    end
    f = File.new(filename, "w")
    result = generateTest i, i

    f.write "#{i} #{i}\n"

    # iterate through rectangles
    result[0].each do |rec|
      f.write(rec.join(' ') + "\n")
    end

    #iterate through points
    result[1].each do |poi|
      f.write(poi.join(' ') + "\n")
    end
    f.close
  end
end
