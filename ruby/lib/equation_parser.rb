require 'pry'
require 'contracts'

class EquationParser
  include Contracts::Core
  include Contracts::Builtin

  attr_accessor :left_hash

  Contract String => String
  def initialize(data)
    @left_hash = {}
    data.each_line do |line|
      split_equation = self.split_on(line, '=')
      @left_hash[split_equation[0]] = split_equation[1]
    end
  end

  Contract String, String => Array
  def split_on(string, character)
    parsed_string = string.split(character)
    parsed_string.each do |item|
      item.strip!
    end
  end

  Contract String => Bool
  def is_integer(string)
    return true if string.is_a? Integer
    string =~ /^\d+$/ ? true : false
  end

  Contract String => String
  def resolve_variable(string)
    @left_hash[string].to_s
  end

  Contract String => Bool
  def contains_operator(string)
    string =~ /[+]+/ ? true : false
  end

  Contract String => String
  def compute(string)
    result = 0
    if is_integer(string)
      return string
    elsif contains_operator(string)
      expanded_string = split_on(string, '+')
      expanded_string.each do |item|
        if is_integer(item)
          result += item.to_i
        else 
          result += compute(resolve_variable(item)).to_i
        end
      end
    else
      result += compute(resolve_variable(string)).to_i
    end
    return result.to_s
  end

  Contract nil => String
  def evaluate
    return_value = []
    @left_hash.each do |key, value|
      result = 0
      operation_array = split_on(value, '+')
      operation_array.each do |operand|
        result += compute(operand.to_s).to_i
      end
      @left_hash[key] = result
      return_value.push("#{key} = #{result}")
    end
    "#{return_value.sort.join("\n")}\n"
  end
end
