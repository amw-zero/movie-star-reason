let printState = (state, label) => {
  Js.log(label);
  Js.log(state^);
};

// Model
type movie = {title: string};

// Application
type movieStarState = {
  movies: array(movie),
  favoritedMovies: list(movie),
};

module Command = {
  let viewTopMovies: movieStarState => movieStarState = state => {
    ...state,
    movies: [|
      {title: "Wayne's World"},
      {title: "Wayne's World 2"},
      {title: "Unabomber"},
      {title: "Cat in the Hat"},
      {title: "Sharkboy and Lavagirl"}, 
    |],
  };
  let toggleFavoriteMovie: (movie, movieStarState) => movieStarState = (movie, state) => {
    let favoritedMovies =
      switch (List.filter(m => m == movie, state.favoritedMovies)) {
      | [] => [movie, ...state.favoritedMovies]
      | _ => List.filter(m => m != movie, state.favoritedMovies)
      };

    {...state, favoritedMovies};
  };
  let clearFavoriteMovies = state => { ...state, favoritedMovies: [] };
};

/*
let state = ref({movies: [||], favoritedMovies: []});
printState(state, "Initial state");

state := Command.viewTopMovies(state^);
state := Command.toggleFavoriteMovie(state^.movies[0], state^);

printState(state, "After favoriting");

state := Command.toggleFavoriteMovie(state^.movies[0], state^);

printState(state, "After update");
*/
