let printState = (state, label) => {
  Js.log(label);
  Js.log(state^);
};

// Model
type movie = {title: string};

// Application

// refactor movies to this type
type asyncData('a) =
  | Pristine
  | Retrieving
  | Retrieved('a)
  | Error;

type movieStarState = {
  movies: array(movie),
  isLoadingMovies: bool,
  favoritedMovies: list(movie),
};

let defaultState = {
  movies: [||],
  isLoadingMovies: false,
  favoritedMovies: [],
};

type dataDependency =
  | TopMovies;

// The next state and any system requests, i.e. "I depend on remote data."
// It's important to say what you need instead of how to do it, as the interpreter
// (execute function) will maintain state and determine
type env = {
  state: movieStarState,
  dataDependency: option(dataDependency),
};

let execute = (f, s, i) => f(s) |> i;

module Command = {
  let asyncTopMovies = (state, server, stateObserver) => {
    let intermediateState = {...state, isLoadingMovies: true};
    stateObserver(intermediateState);

    // dataDependency: Some(TopMovies),    
    server(m =>
      stateObserver({
        ...intermediateState,
        isLoadingMovies: false,
        movies: [|{title: "Test Movie"}|],
      })
    );
  };

  let viewTopMovies: movieStarState => env =
    state => {
      dataDependency: Some(TopMovies),
      state: {
        ...state,
        movies: [|
          {title: "Wayne's World"},
          {title: "Wayne's World 2"},
          {title: "Unabomber"},
          {title: "Cat in the Hat"},
          {title: "Sharkboy and Lavagirl"},
        |],
      },
    };
  let toggleFavoriteMovie: (movie, movieStarState) => movieStarState =
    (movie, state) => {
      let favoritedMovies =
        switch (List.filter(m => m == movie, state.favoritedMovies)) {
        | [] => [movie, ...state.favoritedMovies]
        | _ => List.filter(m => m != movie, state.favoritedMovies)
        };

      {...state, favoritedMovies};
    };
  let clearFavoriteMovies = state => {...state, favoritedMovies: []};
};
