require 'spec_helper'

describe EquationParser do

  context '#initialize' do
    it 'parses the data into a dictionary' do
      data = load_file('fixture1.txt')
      equation_parser = EquationParser.new(data)
      expect(equation_parser.left_hash['answer1']).to eq('1 + 1')
      expect(equation_parser.left_hash['answer2']).to eq('2 + 2')
    end
  end

  context '#split_on_equal' do
    it 'finds the left-hand side of the equation' do
      result = EquationParser.new('').split_on_equal('stuff = 1 + 1')
      expect(result[0]).to eq('stuff')
    end
  end

  context '#split_on_operator' do
    it 'creates an array of operands' do
      result = EquationParser.new('').split_on_operator('1 + 1')
      expect(result[0]).to eq('1')
      expect(result[1]).to eq('1')
    end
  end

  context '#evaluate' do
    context 'with simple input' do
      it 'does the math' do
        data = load_file('fixture1.txt')
        equation_parser = EquationParser.new(data)
        expect(equation_parser.evaluate).to eq("answer1 = 2\nanswer2 = 4")
      end
    end

    context 'with some variables' do
      it 'does the math' do
        data = load_file('fixture2.txt')
        equation_parser = EquationParser.new(data)
        expect(equation_parser.evaluate).to eq("answer1 = 5\nanswer2 = 4")
      end
    end

    context 'with the sample input' do
      it 'does the math' do
        data = load_file('fixture5.txt')
        equation_parser = EquationParser.new(data)
        answer = "location = 16\noffset = 7\norigin = 8\nrandom = 2"
        expect(equation_parser.evaluate).to eq(answer)
      end
    end
  end

  context '#is_integer' do
    context 'with strings' do
      it 'returns true if integer' do
        result = EquationParser.new('').is_integer('1')
        expect(result).to be true
      end

      it 'returns false if string' do
        result = EquationParser.new('').is_integer('a')
        expect(result).to be false
      end
    end
    context 'with integers' do
      it 'returns true if integer' do
        result = EquationParser.new('').is_integer(1)
        expect(result).to be true
      end
    end
  end

  context '#resolve_variable' do
    it 'returns the value of the variable' do
      data = load_file('fixture2.txt')
      equation_parser = EquationParser.new(data)
      expect(equation_parser.resolve_variable('answer2')).to eq('2 + 2')
    end
  end

  context '#compute' do
    context 'with 1 level of resolution' do
      it 'resolves and computes the value of the string' do
        data = load_file('fixture2.txt')
        equation_parser = EquationParser.new(data)
        expect(equation_parser.compute('2 + 2')).to eq(4)
      end
    end
    context 'with 2 levels of resolution' do
      it 'resolves and computes the value of the string' do
        data = load_file('fixture3.txt')
        equation_parser = EquationParser.new(data)
        expect(equation_parser.compute('1 + answer2')).to eq(7)
      end
    end
    context 'with 3 levels of resolution' do
      it 'resolves and computes the value of the string' do
        data = load_file('fixture4.txt')
        equation_parser = EquationParser.new(data)
        expect(equation_parser.compute('1 + answer2')).to eq(9)
      end
    end
  end
end
