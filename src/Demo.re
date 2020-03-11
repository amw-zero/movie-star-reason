type movie = {title: string};

type movieStarState = {movies: list(movie)};

let state = ref({movies: [{title: "Wayne's World"}]});

Js.log(state^);

state := {movies: [{title: "Sharkboy and Lavagirl"}]};

Js.log(state^);
