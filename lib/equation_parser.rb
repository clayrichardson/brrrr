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
      split_equation = self.split_on_equal(line)
      @left_hash[split_equation[0]] = split_equation[1]
    end
  end

  Contract String => Array
  def split_on_equal(string)
    parsed_string = string.split('=')
    parsed_string.each do |item|
      item.strip!
    end
  end

  Contract String => Array
  def split_on_operator(string)
    parsed_string = string.split('+')
    parsed_string.each do |item|
      item.strip!
    end
  end

  Contract Or[String, Int] => Bool
  def is_integer(string)
    return true if string.is_a? Integer
    string =~ /^\d+$/ ? true : false
  end

  Contract String => Or[String, Int]
  def resolve_variable(string)
    @left_hash[string]
  end

  Contract Or[String, Int] => Or[String, Int]
  def compute(string)
    result = 0
    if is_integer(string)
      return string.to_i
    else 
      expanded_string = split_on_operator(string)
    end
    expanded_string.each do |item|
      if is_integer(item)
        result += item.to_i
      else 
        result += compute(resolve_variable(item))
      end
    end
    return result
  end

  Contract nil => String
  def evaluate
    return_value = []
    @left_hash.each do |key, value|
      result = 0
      operation_array = split_on_operator(value)
      operation_array.each do |operand|
        result += compute(operand)
      end
      @left_hash[key] = result
      return_value.push("#{key} = #{result}")
    end
    return_value.sort.join("\n")
  end

end
