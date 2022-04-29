define psyms
	set var $i = 0
	while ($i < $arg1)
		if $arg0[$i].x64
			p *$arg0[$i].x64
		else
			if $arg0[$i].x86
				p *$arg0[$i].x86
			else
				p "NULL"
			end
		end
		set var $i++
	end
end
