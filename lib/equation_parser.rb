require 'pry'

class EquationParser

  attr_accessor :left_hash

  def initialize(data)
    @left_hash = {}
    data.each_line do |line|
      split_equation = self.split_on_equal(line)
      @left_hash[split_equation[0]] = split_equation[1]
    end
  end

  def split_on_equal(string)
    parsed_string = string.split('=')
    parsed_string.each do |item|
      item.strip!
    end
  end

  def split_on_operator(string)
    parsed_string = string.split('+')
    parsed_string.each do |item|
      item.strip!
    end
  end

  def is_integer(string)
    return true if string.is_a? Integer
    string =~ /^\d+$/ ? true : false
  end

  def resolve_variable(string)
    @left_hash[string]
  end

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
    return_value.join("\n")
  end

end
