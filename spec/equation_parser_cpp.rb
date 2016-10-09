require 'spec_helper'

describe EquationParser do

  context 'the cli' do
    it 'returns an error if no filename is given' do
      stdout, stderr, status = run_cli("")
      expect(stderr).to eq("Usage: EquationParser <path_to_input_file>\n")
    end

    it 'returns an error if no data was read from file' do
      stdout, stderr, status = run_cli('not_a_file.txt')
      expect(stderr).to eq("Error: empty file\n")
    end

    it 'does the math with simple input' do
      stdout, stderr, status = run_cli('fixture1.txt')
      expect(stdout).to eq("answer1 = 2\nanswer2 = 4\n")
    end

    it 'does the math with some variables' do
      stdout, stderr, status = run_cli('fixture2.txt')
      expect(stdout).to eq("answer1 = 5\nanswer2 = 4\n")
    end

    it 'does the math with the sample input' do
      stdout, stderr, status = run_cli('fixture5.txt')
      answer = "location = 16\noffset = 7\norigin = 8\nrandom = 2\n"
      expect(stdout).to eq(answer)
    end
    it 'does the math with the crazy input' do
      stdout, stderr, status = run_cli('fixture6.txt')
      answer = "bacon = 285\ncrazy = 303\nit = 35\nitems = 180\nkeep = 45\nlocation = 319\noffset = 7\norigin = 8\nrandom = 2\nstuff = 35\nthings = 35\n"
      expect(stdout).to eq(answer)
    end
  end
end
